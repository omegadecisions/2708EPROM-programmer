# 2708EPROM-programmer
# Prototype v.01
## Preface

Most modern electronic programmers do not support obsolete NMOS EPROM chips such as Intel 2708.

There are several reasons:
```
1) Three supply voltages
2) High voltage programming
```

However, these EPROM chips are actively used by retro computing enthusiasts - as they are present in many designs of retro computers

### Technical task
```
Build the prototype of electronic programmer for Intel 2708 EPROM
```

A device capable of programming such a chip was needed in the process of working on a replica of a homemade 8-bit retrocomputer:
A homemade 8-bit retrocomputer [Radio-88RK](http://archive.radio.ru/web/1986/05/035/)

### Process

Two publications served as the basis for prototyping:

1) Article of author of replica russian 8-bit retro-computer [Specialist-Express](https://habr.com/ru/post/247211/)

2) Version of programmer for another russian 8-bit microcomputer "Radio micro-80" published in popular russian magazine "Radio":
Programmer for 2708 EPROM [Micro-80](http://archive.radio.ru/web/1983/06/049/)


>Device No. 1 was intended for programming EPROM 2716 (which differed from 2708 in just one supply voltage and a different programming algorithm). The fragment of electonic circuit was not applicable for controlling of pulses Vpp 2708
>
>Device No. 2 contained the required Vpp voltage control driver solution for 2708.



As a result, a prototype was created, which was a compilation of these two devices.
In addition to this, in software folder there is program code for Intel-8080 (it waz disassembled from dump of article 2)
