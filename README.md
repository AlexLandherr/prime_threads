# prime_threads
Multi-threaded benchmark in C++ that searches for prime numbers. 

# Install & Use
First clone the repo:
```
git clone https://github.com/AlexLandherr/prime_threads.git
```
Change directory to repo:
```
cd prime_threads/
```
Create a directory called `obj` and `logs`:
```
mkdir {obj,logs}
```
Then build & compile using `make`:
```
make
```

Run:
```
./prime_threads
```

# Performance Examples
## My Hardware
### Development System Results
Specs of my dev machine:
```
alexl@PD70PNP:~$ neofetch
       _,met$$$$$gg.          alexl@PD70PNP 
    ,g$$$$$$$$$$$$$$$P.       ------------- 
  ,g$$P"     """Y$$.".        OS: Debian GNU/Linux 12 (bookworm) x86_64 
 ,$$P'              `$$$.     Host: PD5x_7xPNP_PNR_PNN_PNT 
',$$P       ,ggs.     `$$b:   Kernel: 6.1.0-13-amd64 
`d$$'     ,$P"'   .    $$$    Uptime: 1 day, 4 hours, 45 mins 
 $$P      d$'     ,    $$P    Packages: 1748 (dpkg) 
 $$:      $$.   -    ,d$$'    Shell: bash 5.2.15 
 $$;      Y$b._   _,d$P'      Resolution: 1920x1080 
 Y$$.    `.`"Y$$$$P"'         DE: GNOME 43.6 
 `$$b      "-.__              WM: Mutter 
  `Y$$                        WM Theme: Adwaita 
   `Y$$.                      Theme: Adwaita [GTK2/3] 
     `$$b.                    Icons: Adwaita [GTK2/3] 
       `Y$$b.                 Terminal: gnome-terminal 
          `"Y$b._             CPU: 12th Gen Intel i7-12700H (20) @ 4.600GHz 
              `"""            GPU: NVIDIA GeForce RTX 3060 Mobile / Max-Q 
                              GPU: Intel Alder Lake-P 
                              Memory: 2912MiB / 15693MiB
```

Example of my results at maximum CPU power limits configurable from Debian:
```
**** Results ****
Program mode is: Multithreaded
Thread count: 20
Search started at: 2023-10-22 16:30:55 UTC
Search ended at: 2023-10-22 16:32:12 UTC
Search ran for total of (DD:HH:MM:SS.SSSSSSSSS): 00:00:01:17.107750325

Search ran for: 77107750325 ns

Average time to find all primes between 1 and 100000000 was (DD:HH:MM:SS.SSSSSSSSS):
00:00:00:07.710763478

Average search time: 7710763478 ns
Number of primes found is: 5761455

**** Runtime for each iteration ****
Iteration 1 of 10 Runtime (ns): 5532404201
Iteration 2 of 10 Runtime (ns): 5927623802
Iteration 3 of 10 Runtime (ns): 7759769464
Iteration 4 of 10 Runtime (ns): 8232699929
Iteration 5 of 10 Runtime (ns): 8213834288
Iteration 6 of 10 Runtime (ns): 8312342055
Iteration 7 of 10 Runtime (ns): 8300434394
Iteration 8 of 10 Runtime (ns): 8311362315
Iteration 9 of 10 Runtime (ns): 8145469869
Iteration 10 of 10 Runtime (ns): 8371694464

Program started at: 2023-10-22 16:30:48 UTC
Program ended at: 2023-10-22 16:32:12 UTC
Program ran for a total of (DD:HH:MM:SS.SSSSSSSSS): 00:00:01:24.090159261
```
### On a ASUS PN64-E1
Specs of PN64-E1:
```
alexl@memory-alpha:~$ neofetch
       _,met$$$$$gg.          alexl@memory-alpha
    ,g$$$$$$$$$$$$$$$P.       ------------------
  ,g$$P"     """Y$$.".        OS: Debian GNU/Linux 12 (bookworm) x86_64
 ,$$P'              `$$$.     Host: MINIPC PN64-E1
',$$P       ,ggs.     `$$b:   Kernel: 6.1.0-11-amd64
`d$$'     ,$P"'   .    $$$    Uptime: 3 hours, 5 mins
 $$P      d$'     ,    $$P    Packages: 517 (dpkg)
 $$:      $$.   -    ,d$$'    Shell: bash 5.2.15
 $$;      Y$b._   _,d$P'      Terminal: /dev/pts/0
 Y$$.    `.`"Y$$$$P"'         CPU: 13th Gen Intel i7-13700H (20) @ 4.800GHz
 `$$b      "-.__              GPU: Intel Raptor Lake-P [UHD Graphics]
  `Y$$                        Memory: 310MiB / 15709MiB
   `Y$$.
     `$$b.
       `Y$$b.
          `"Y$b._
              `"""
```

Example run on PN64-E1:
```
**** Results ****
Program mode is: Multithreaded
Thread count: 20
Search started at: 2023-09-05 18:50:00 UTC
Search ended at: 2023-09-05 18:51:03 UTC
Search ran for total of (DD:HH:MM:SS.SSSSSSSSS): 00:00:01:02.484791592

Search ran for: 62484791592 ns

Average time to find all primes between 1 and 100000000 was (DD:HH:MM:SS.SSSSSSSSS):
00:00:00:06.248471420

Average search time: 6248471420 ns
Number of primes found is: 5761455

**** Runtime for each iteration ****
Iteration 1 of 10 Runtime (ns): 6170955048
Iteration 2 of 10 Runtime (ns): 6422582420
Iteration 3 of 10 Runtime (ns): 6126953291
Iteration 4 of 10 Runtime (ns): 6176520018
Iteration 5 of 10 Runtime (ns): 6097712673
Iteration 6 of 10 Runtime (ns): 6270516635
Iteration 7 of 10 Runtime (ns): 6364187311
Iteration 8 of 10 Runtime (ns): 6309591198
Iteration 9 of 10 Runtime (ns): 6245590917
Iteration 10 of 10 Runtime (ns): 6300104691

Program started at: 2023-09-05 18:49:53 UTC
Program ended at: 2023-09-05 18:51:03 UTC
Program ran for a total of (DD:HH:MM:SS.SSSSSSSSS): 00:00:01:09.775377205
```
## Other People's Hardware
### Jeff Geerling's Results
A run on a 96-core Ampere Altra ARM CPU thanks to [@geerlingguy](https://github.com/geerlingguy):
- [Ampere Altra Developer Platform](https://github.com/geerlingguy/sbc-reviews/issues/19)
- [Link to Jeff Geerling's results](https://github.com/geerlingguy/sbc-reviews/issues/19#issuecomment-1620919247)
```
jgeerling@adlink-ampere:~/prime_threads$ ./prime_threads
System supports 96 threads.
    ****    
Search limit for all options are (both are inclusive limits):
Lower search limit: 1
Upper search limit: 100000000

Select benchmark mode from list below:
0. Single-threaded benchmark.
1. Multi-threaded benchmark (96 threads).
2. Exit program.
Enter one of the listed values: 1

Numerator (also upper search limit): 100000000
Denominator (also how many threads): 96
Quotient: 1041666
Remainder: 64
  ****  
Starting multithreaded prime benchmark...

Started at: 2023-07-05 02:10:34 UTC
Iteration 1 of 10 Runtime (ns): 1650924933
Iteration 2 of 10 Runtime (ns): 1381674931
Iteration 3 of 10 Runtime (ns): 1381530659
Iteration 4 of 10 Runtime (ns): 1381874490
Iteration 5 of 10 Runtime (ns): 1382733573
Iteration 6 of 10 Runtime (ns): 1380218386
Iteration 7 of 10 Runtime (ns): 1392295779
Iteration 8 of 10 Runtime (ns): 1380862075
Iteration 9 of 10 Runtime (ns): 1381572084
Iteration 10 of 10 Runtime (ns): 1381265241
Prime multithreaded benchmark is done!

Stopped at: 2023-07-05 02:10:48 UTC

**** Results ****
Program mode is: Multithreaded
Thread count: 96
Search started at: 2023-07-05 02:10:34 UTC
Search ended at: 2023-07-05 02:10:48 UTC
Program ran for total of (DD:HH:MM:SS.SSSSSSSSS): 00:00:00:14.095112951

Program ran for: 14095112951 ns

Average time to find all primes between 1 and 100000000 was (DD:HH:MM:SS.SSSSSSSSS):
00:00:00:01.409495215

Average search time: 1409495215 ns
Number of primes found is: 5761455
```
