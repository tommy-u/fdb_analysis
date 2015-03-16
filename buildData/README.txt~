dosCSV2Mac converts dos CR files to unix friendly \n line endings 
there is an element with no sex reported 
Removed entry 2280,T-394R,,,,,,,,,,,TER,159,14,12,169,105,330,,48,25,18,247,13,19,257,17,16,230,,92,108,44,223,158,,,410,409,82,47,31,35,32,21,92,351,80,52,31,23,89,357,14,77,45,
By hand because had no sex assignment.
Note item 3798 says birth year 1995, age 49
Removed by hand. 
Write Locked Cranial and Postcranial

Grabs Sex and 7 measurements we want
(cat Postcranial |  cut -d ',' -f 5,19,24,27,39,40,48,54) > tmp
./createTrain tmp > tmp2
cat tmp2 | cut -d ' ' -f 1 > tmp3
cat tmp2 | cut -d ' ' -f 2-8 > tmp4
paste -d '\n' tmp4 tmp5 > tmp5
remove first 2 lines
6008 lines, 3004 specimines
Put every other in train / test after converting M and F to 0 and 1
cat tmp5 | tr 'M' '0' | tr 'F' '1' > tmp6



