# UE-DevLog
用于个人的开发学习问题记录

### [Log #001] 2026-06-28 ｜ 虚幻编辑器与 OS 文件锁冲突挂起

<details>
<summary> 点击展开查看排查详情与底层成因</summary>

```text
[Crash/Error] 开启虚幻编辑器与 Live Coding 的情况下，VS Build Failed - LNK1104: 无法打开文件 MyCPP.dll
[Reason]      操作系统的独占锁（Exclusive Lock）冲突。UE 编辑器进程正在占用该 DLL。
[Fix]         - 修改 .cpp：使用 Ctrl + Alt + F11 执行 Live Coding热补丁缝合。
              - 修改 .h：关闭 UE 编辑器后再进行 VS 编译。
