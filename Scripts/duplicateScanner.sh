#!/bin/bash
i=-999
j=-999
#MuOnia_Run2012C_22Jan2013-v1_HLT_JpsiORUpsilon_Oct2015Skim_99_1_x7X.root
ls /data/cms_data3/2012_MuOnia_HLTSkim/MuOnia_Run2012D-22Jan2013-v1_HLTSkim/*.root | while IFS=_ read first second third fourth fifth sixth seventh eighth ninth tenth eleventh twelfth thirteenth fourteenth;
  do
  i=$twelfth
  if [ $i = $j ]; then
    echo "$i $j"
    echo "$twelfth $thirteenth"
  fi
  j=$twelfth


#  echo $eighth
#  echo $ninth
#  echo $tenth
#  echo $fourteenth

  done 




