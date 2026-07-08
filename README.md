# UE-DevLog
用于个人的开发学习问题记录

### [Log #001] 2026-06-30 ｜ C++ 与 Live Coding 编译导致的文件锁和蓝图数据不刷新

<details>
<summary>点击展开查看排查详情与底层成因</summary>
<pre>
[Crash/Error]
1. 开启 Unreal Editor 且启用 Live Coding 时，在 VS 执行 Build：
   LNK1104: 无法打开文件 UnrealEditor-MyProject.dll

2. 修改 Projectile 构造函数、碰撞默认值等代码后，
   Live Coding 编译成功，但 Blueprint 仍使用旧默认值，
   表现为 OnComponentHit 等事件不生效，清理缓存或完整 Build 后恢复正常。

[Reason]
1. UE Editor 已加载项目 DLL，操作系统会对 DLL 加独占锁（Exclusive Lock），
   VS 无法覆盖 DLL，因此 Link 阶段失败（LNK1104）。

2. Live Coding 本质是运行时热补丁，仅更新已编译的函数实现，
   不会完整重建 UObject 反射信息、Blueprint CDO（Class Default Object）
   及部分序列化缓存。涉及 UPROPERTY、构造函数、组件创建、
   默认值等修改时，Blueprint 可能继续使用旧数据。

[Fix]
- 修改普通 .cpp 逻辑：
  使用 Ctrl + Alt + F11（Live Coding）。

- 修改 .h、UPROPERTY、UFUNCTION、CreateDefaultSubobject()、
  RootComponent、构造函数默认值等 UObject 结构：
  关闭 UE Editor → VS Build → 重新打开 UE。

- 若出现 Blueprint 不刷新、默认值失效、事件异常等问题：
  删除 Binaries、Intermediate 等中间文件后重新 Build。
</pre>
</details>

---

### [Log #002] 2026-07-08 ｜ 高速运动组件生成帧物理穿透导致的子弹生成即自毁

<details>
<summary>点击展开查看排查详情与底层成因</summary>
<pre>
[Crash/Error]
1. 在坦克（Tank）处于静态或后退状态时，点击开火（Fire），子弹发射完全正常。
2. 当坦克处于全速前进或加速移动状态时，点击开火，子弹完全无法射出。
3. 通过控制台与日志排查发现：子弹在被生成出来的瞬间，在炮口位置直接触发了 OnHit 事件，并立刻执行了自毁逻辑。

[Reason]
1. 物理引擎的碰撞帧重叠机制（Penetration）：
   当坦克全速前进时，由于物理线速度较快，在执行 `SpawnActor` 孵化子弹的这一帧，子弹的物理碰撞体与坦克炮口的物理碰撞体在空间上产生了一定程度的重叠。
2. 物理事件误判：
   虚幻引擎物理系统在计算下一帧位置时，检测到两个 Collision 处于相交状态（Overlapped/Blocking），从而强行触发了子弹的 `OnComponentHit` 委托。

[Fix]
- 注入 Actor 归属关系（Owner 绑定）：
  在调用 `SpawnActor` 孵化子弹时，配置 `FActorSpawnParameters` 结构体，显式将 `SpawnParams.Owner = this`（即发射该子弹的坦克），让子弹在出生时具备合法的属主血缘。
- 物理移动动态免疫（IgnoreActorWhenMoving）：
  在子弹类的 `BeginPlay` 阶段，获取其碰撞组件，并结合已绑定的 Owner（Tank），调用 `IgnoreActorWhenMoving` 函数，显式告知物理引擎：当此子弹在高频移动时，无视与主人碰撞体的交叠计算，从根本上免疫开火帧的自毁 Bug。
</pre>
</details>
