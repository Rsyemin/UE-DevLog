# UE-DevLog
用于个人的开发学习问题记录

### [Log #001] 2026-06-30 ｜ C++ 与 Live Coding 编译导致的文件锁和蓝图数据不刷新

<details>
<summary> 点击展开查看排查详情与底层成因</summary>

```text
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
