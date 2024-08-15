# NoBsod
Remove BSOD from your system

![Meme](assets/bsod_smile.png)

### How it works
Exportable KeBugCheckEx function calls when an error occurred in kernel mode. We can simply hook this function and sleep thread for infinity time

### Pictures
![](assets/img.png)

### Code
https://github.com/Umbre11as/NoBsodDriver/blob/master/src/main.cpp#L6-L16

https://github.com/Umbre11as/NoBsodDriver/blob/master/src/main.cpp#L21-L27

### References
[kCaveHook](https://github.com/Umbre11as/kCaveHook)

[Zydis](https://github.com/zyantific/zydis)
