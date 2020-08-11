EESchema Schematic File Version 4
LIBS:TeensyPCB-cache
EELAYER 26 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 1
Title "Teensy PCB"
Date "2020-08-07"
Rev "1"
Comp "Sohom Roy"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CustomLibrary:Teensy-LC U2
U 1 1 5F2FF675
P 3600 2650
F 0 "U2" H 3625 1413 60  0000 C CNN
F 1 "Teensy-LC" H 3625 1519 60  0000 C CNN
F 2 "CustomFootprints:Teensy30_31_32_LC_nopogo" H 3600 2100 60  0001 C CNN
F 3 "" H 3600 2100 60  0000 C CNN
	1    3600 2650
	-1   0    0    1   
$EndComp
$Comp
L CustomLibrary:Teensy-LC U4
U 1 1 5F3013CB
P 7250 2650
F 0 "U4" H 7275 1413 60  0000 C CNN
F 1 "Teensy-LC" H 7275 1519 60  0000 C CNN
F 2 "CustomFootprints:Teensy30_31_32_LC_nopogo" H 7250 2100 60  0001 C CNN
F 3 "" H 7250 2100 60  0000 C CNN
	1    7250 2650
	-1   0    0    1   
$EndComp
$Comp
L CustomLibrary:Teensy-LC U1
U 1 1 5F302D19
P 3550 5350
F 0 "U1" H 3575 6587 60  0000 C CNN
F 1 "Teensy-LC" H 3575 6481 60  0000 C CNN
F 2 "CustomFootprints:Teensy30_31_32_LC_nopogo" H 3550 4800 60  0001 C CNN
F 3 "" H 3550 4800 60  0000 C CNN
	1    3550 5350
	1    0    0    -1  
$EndComp
$Comp
L CustomLibrary:Teensy-LC U3
U 1 1 5F312DB2
P 7200 5350
F 0 "U3" H 7225 6587 60  0000 C CNN
F 1 "Teensy-LC" H 7225 6481 60  0000 C CNN
F 2 "CustomFootprints:Teensy30_31_32_LC_nopogo" H 7200 4800 60  0001 C CNN
F 3 "" H 7200 4800 60  0000 C CNN
	1    7200 5350
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female J10
U 1 1 5F3148A0
P 9250 3950
F 0 "J10" H 9278 3926 50  0000 L CNN
F 1 "Conn_01x02_Female" H 9278 3835 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 9250 3950 50  0001 C CNN
F 3 "~" H 9250 3950 50  0001 C CNN
	1    9250 3950
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J1
U 1 1 5F316FFB
P 1450 3950
F 0 "J1" H 1558 4131 50  0000 C CNN
F 1 "Conn_01x02_Male" H 1558 4040 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 1450 3950 50  0001 C CNN
F 3 "~" H 1450 3950 50  0001 C CNN
	1    1450 3950
	1    0    0    -1  
$EndComp
Text GLabel 1400 3950 0    50   Input ~ 0
GND
Text GLabel 1400 4050 0    50   Input ~ 0
RX
$Comp
L power:GND #PWR04
U 1 1 5F325555
P 5150 2000
F 0 "#PWR04" H 5150 1750 50  0001 C CNN
F 1 "GND" V 5155 1872 50  0000 R CNN
F 2 "" H 5150 2000 50  0001 C CNN
F 3 "" H 5150 2000 50  0001 C CNN
	1    5150 2000
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5F32643E
P 8800 2000
F 0 "#PWR08" H 8800 1750 50  0001 C CNN
F 1 "GND" V 8805 1872 50  0000 R CNN
F 2 "" H 8800 2000 50  0001 C CNN
F 3 "" H 8800 2000 50  0001 C CNN
	1    8800 2000
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5F3289E5
P 1900 6000
F 0 "#PWR01" H 1900 5750 50  0001 C CNN
F 1 "GND" V 1905 5872 50  0000 R CNN
F 2 "" H 1900 6000 50  0001 C CNN
F 3 "" H 1900 6000 50  0001 C CNN
	1    1900 6000
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5F3292EB
P 5250 5200
F 0 "#PWR05" H 5250 4950 50  0001 C CNN
F 1 "GND" V 5255 5072 50  0000 R CNN
F 2 "" H 5250 5200 50  0001 C CNN
F 3 "" H 5250 5200 50  0001 C CNN
	1    5250 5200
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5F32A39B
P 8850 5200
F 0 "#PWR09" H 8850 4950 50  0001 C CNN
F 1 "GND" V 8855 5072 50  0000 R CNN
F 2 "" H 8850 5200 50  0001 C CNN
F 3 "" H 8850 5200 50  0001 C CNN
	1    8850 5200
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5F32AA4F
P 5600 6000
F 0 "#PWR06" H 5600 5750 50  0001 C CNN
F 1 "GND" V 5605 5872 50  0000 R CNN
F 2 "" H 5600 6000 50  0001 C CNN
F 3 "" H 5600 6000 50  0001 C CNN
	1    5600 6000
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5F32FF52
P 5650 2800
F 0 "#PWR07" H 5650 2550 50  0001 C CNN
F 1 "GND" V 5655 2672 50  0000 R CNN
F 2 "" H 5650 2800 50  0001 C CNN
F 3 "" H 5650 2800 50  0001 C CNN
	1    5650 2800
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5F33068E
P 2000 2800
F 0 "#PWR02" H 2000 2550 50  0001 C CNN
F 1 "GND" V 2005 2672 50  0000 R CNN
F 2 "" H 2000 2800 50  0001 C CNN
F 3 "" H 2000 2800 50  0001 C CNN
	1    2000 2800
	0    1    1    0   
$EndComp
Wire Wire Line
	8400 3600 8450 3600
Wire Wire Line
	8450 3600 8450 3950
Connection ~ 8450 3950
Wire Wire Line
	8450 3950 9050 3950
Wire Wire Line
	4750 3600 4800 3600
Wire Wire Line
	4800 3600 4800 3950
Connection ~ 4800 3950
$Comp
L power:GND #PWR03
U 1 1 5F337D63
P 3950 3800
F 0 "#PWR03" H 3950 3550 50  0001 C CNN
F 1 "GND" H 3955 3627 50  0000 C CNN
F 2 "" H 3950 3800 50  0001 C CNN
F 3 "" H 3950 3800 50  0001 C CNN
	1    3950 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 3800 3700 3800
Wire Wire Line
	3700 3800 3700 3950
Connection ~ 3700 3950
Wire Wire Line
	3700 3950 4800 3950
Wire Wire Line
	8750 3500 8750 4050
Connection ~ 8750 4050
Wire Wire Line
	8750 4050 9050 4050
Connection ~ 1650 3950
Wire Wire Line
	1650 3950 1400 3950
Connection ~ 1650 4050
Wire Wire Line
	1650 4050 1400 4050
Wire Wire Line
	5150 3500 5150 4050
Connection ~ 5150 4050
Wire Wire Line
	2000 2800 2400 2800
Wire Wire Line
	4750 3500 5150 3500
Wire Wire Line
	4750 2000 5150 2000
Wire Wire Line
	8400 2000 8800 2000
Wire Wire Line
	5650 2800 6050 2800
Wire Wire Line
	1900 6000 2400 6000
Wire Wire Line
	1650 3950 2400 3950
Wire Wire Line
	1650 4050 2150 4050
Wire Wire Line
	4750 5200 5250 5200
Wire Wire Line
	5600 6000 6050 6000
Wire Wire Line
	5150 4050 5850 4050
Wire Wire Line
	4800 3950 6050 3950
Wire Wire Line
	8400 5200 8850 5200
Wire Wire Line
	2400 4400 2400 3950
Connection ~ 2400 3950
Wire Wire Line
	2400 3950 3700 3950
Wire Wire Line
	6050 4400 6050 3950
Connection ~ 6050 3950
Wire Wire Line
	6050 3950 8450 3950
Wire Wire Line
	6050 4500 5850 4500
Wire Wire Line
	5850 4500 5850 4050
Connection ~ 5850 4050
Wire Wire Line
	5850 4050 8750 4050
Wire Wire Line
	2400 4500 2150 4500
Wire Wire Line
	2150 4500 2150 4050
Connection ~ 2150 4050
Wire Wire Line
	2150 4050 5150 4050
Wire Wire Line
	8400 3500 8750 3500
$EndSCHEMATC