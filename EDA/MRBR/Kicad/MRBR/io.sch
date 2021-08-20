EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 4000 1100 0    50   Input ~ 0
GPIOs
Text HLabel 4000 1200 0    50   Input ~ 0
I2C
Text HLabel 4000 1300 0    50   Input ~ 0
UART1
Text HLabel 4000 1400 0    50   Input ~ 0
UART2
Wire Bus Line
	4000 1100 6000 1100
Entry Wire Line
	6000 1100 6100 1200
Entry Wire Line
	6000 1200 6100 1300
Entry Wire Line
	6000 1300 6100 1400
Entry Wire Line
	6000 1400 6100 1500
Entry Wire Line
	6000 1500 6100 1600
Entry Wire Line
	6000 1700 6100 1800
Entry Wire Line
	6000 1600 6100 1700
Text Label 6200 1200 0    50   ~ 0
BT_LED
$Comp
L Device:LED D4
U 1 1 611CD8F5
P 7300 1200
F 0 "D4" H 7293 945 50  0000 C CNN
F 1 "LED" H 7293 1036 50  0000 C CNN
F 2 "" H 7300 1200 50  0001 C CNN
F 3 "~" H 7300 1200 50  0001 C CNN
	1    7300 1200
	-1   0    0    1   
$EndComp
$Comp
L Device:R R9
U 1 1 611CECE2
P 6850 1200
F 0 "R9" V 6643 1200 50  0000 C CNN
F 1 "220R" V 6734 1200 50  0000 C CNN
F 2 "" V 6780 1200 50  0001 C CNN
F 3 "~" H 6850 1200 50  0001 C CNN
	1    6850 1200
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR022
U 1 1 611CF611
P 8050 1200
F 0 "#PWR022" H 8050 950 50  0001 C CNN
F 1 "GND" H 8055 1027 50  0000 C CNN
F 2 "" H 8050 1200 50  0001 C CNN
F 3 "" H 8050 1200 50  0001 C CNN
	1    8050 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 1200 6700 1200
Wire Wire Line
	7000 1200 7150 1200
Wire Wire Line
	7450 1200 8050 1200
Wire Bus Line
	6000 1100 6000 2150
$EndSCHEMATC
