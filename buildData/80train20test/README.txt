
(cat Postcranial |  cut -d ',' -f 5,19,24,27,39,40,48,54) > allDataBothSex
/usr/local/bin/gshuf allInputsFem -o allInputsFem
We can grab first n because we shuffeled them randomly
tommyu$ wc -l allInputsFem 
     631 allInputsFem
need to grab first 631 * .8 = 504  for train
head -n 504 allInputsFem
need to grab rest for test 
tail -n +505 allInputsFem

cumm111-0b01-dhcp181:80train20test tommyu$ wc -l allInputsFemTrain 
     504 allInputsFemTrain
cumm111-0b01-dhcp181:80train20test tommyu$ wc -l allInputsFemTest
     127 allInputsFemTest

Now grab first 504 from allInputsMale
store in allInputsMaleTrain
same for Fem

cumm111-0b01-dhcp181:80train20test tommyu$ paste -d '\n'  <( cat allInputsMaleTrain) <( cat allInputsFemTrain) > allInputsTrain
cumm111-0b01-dhcp181:80train20test tommyu$ paste -d '\n'  <( cat allInputsMaleTest) <( cat allInputsFemTest) > allInputsTest

cumm111-0b01-dhcp181:80train20test tommyu$ wc -l allInputsTrain 
    1008 allInputsTrain
cumm111-0b01-dhcp181:80train20test tommyu$ wc -l allInputsTest 
     254 allInputsTest

Make sure there are no repeated entries

tommyu$ cat allInputsTrain allInputsTest | sort | uniq -c

shuffle them 
tommyu$ gshuf allInputsTest -o allInputsTest
cumm111-0b01-dhcp181:80train20test tommyu$ gshuf allInputsTrain -o allInputsTrain 

cumm111-0b01-dhcp181:80train20test tommyu$ paste -d '\n' <(cat allInputsTrain | cut -d ' ' -f 2-8) <(cat allInputsTrain | cut -d ' ' -f 1) > allInputTrainIO
cumm111-0b01-dhcp181:80train20test tommyu$ paste -d '\n' <(cat allInputsTest | cut -d ' ' -f 2-8) <(cat allInputsTest | cut -d ' ' -f 1) > allInputTestIO

make into fann readable files 

cumm111-0b01-dhcp181:80train20test tommyu$ cat allInputTrainIO | tr 'F' '1' | tr 'M' '0' > fannTrain.data
cumm111-0b01-dhcp181:80train20test tommyu$ cat allInputTestIO | tr 'F' '1' | tr 'M' '0' > fannTest.data

and add headers 
