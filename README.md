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
Specs of my dev machine:
```
alexl@PD70PNP:~$ neofetch
            .-/+oossssoo+/-.               alexl@PD70PNP 
        `:+ssssssssssssssssss+:`           ------------- 
      -+ssssssssssssssssssyyssss+-         OS: Ubuntu 22.04.2 LTS x86_64 
    .ossssssssssssssssssdMMMNysssso.       Host: PD5x_7xPNP_PNR_PNN_PNT 
   /ssssssssssshdmmNNmmyNMMMMhssssss/      Kernel: 6.1.0-1015-oem 
  +ssssssssshmydMMMMMMMNddddyssssssss+     Uptime: 20 hours, 8 mins 
 /sssssssshNMMMyhhyyyyhmNMMMNhssssssss/    Packages: 2048 (dpkg), 16 (snap) 
.ssssssssdMMMNhsssssssssshNMMMdssssssss.   Shell: bash 5.1.16 
+sssshhhyNMMNyssssssssssssyNMMMysssssss+   Resolution: 1920x1080 
ossyNMMMNyMMhsssssssssssssshmmmhssssssso   DE: GNOME 42.5 
ossyNMMMNyMMhsssssssssssssshmmmhssssssso   WM: Mutter 
+sssshhhyNMMNyssssssssssssyNMMMysssssss+   WM Theme: Adwaita 
.ssssssssdMMMNhsssssssssshNMMMdssssssss.   Theme: Yaru [GTK2/3] 
 /sssssssshNMMMyhhyyyyhdNMMMNhssssssss/    Icons: Yaru [GTK2/3] 
  +sssssssssdmydMMMMMMMMddddyssssssss+     Terminal: gnome-terminal 
   /ssssssssssshdmNNNNmyNMMMMhssssss/      CPU: 12th Gen Intel i7-12700H (20) @ 4.600GHz 
    .ossssssssssssssssssdMMMNysssso.       GPU: NVIDIA GeForce RTX 3060 Mobile / Max-Q 
      -+sssssssssssssssssyyyssss+-         GPU: Intel Alder Lake-P 
        `:+ssssssssssssssssss+:`           Memory: 3480MiB / 15691MiB 
            .-/+oossssoo+/-.
```

Example of my results at maximum CPU power limits configurable from Ubuntu:
```
Program mode is: Multithreaded
Thread count: 20
Search started at: 2023-07-05 08:33:13 UTC
Search ended at: 2023-07-05 08:34:11 UTC
Program ran for total of (DD:HH:MM:SS.SSSSSSSSS): 00:00:00:58.569630496

Program ran for: 58569630496 ns

Average time to find all primes between 1 and 100000000 was (DD:HH:MM:SS.SSSSSSSSS):
00:00:00:05.856952223

Average search time: 5856952223 ns
Number of primes found is: 5761455

**** Runtime for each iteration ****
Iteration 1 of 10 Runtime (ns): 5806562542
Iteration 2 of 10 Runtime (ns): 5679193186
Iteration 3 of 10 Runtime (ns): 5739044034
Iteration 4 of 10 Runtime (ns): 5868012868
Iteration 5 of 10 Runtime (ns): 5759130597
Iteration 6 of 10 Runtime (ns): 5850852134
Iteration 7 of 10 Runtime (ns): 6006729002
Iteration 8 of 10 Runtime (ns): 5994649762
Iteration 9 of 10 Runtime (ns): 5895252589
Iteration 10 of 10 Runtime (ns): 5970095523

Program started at: 2023-07-05 08:33:04 UTC
Program ended at: 2023-07-05 08:34:11 UTC
```

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
