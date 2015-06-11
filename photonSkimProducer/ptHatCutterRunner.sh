#root -l -b -q 'ptHatCutter.C+(30,50,40)'
#root -l -b -q 'ptHatCutter.C+(50,80,40)'
#root -l -b -q 'ptHatCutter.C+(80,120,40)'
#root -l -b -q 'ptHatCutter.C+(120,170,40)'
#root -l -b -q 'ptHatCutter.C+(170,9999,40)'

g++ ptHatCutter.C $(root-config --cflags --libs) -Wall -Wextra -g -o ptHatCutter.exe

input="/export/d00/scratch/tatar/output/merged_pPb_Pbp_MIX_AllQCDPhoton30_50_80_120_170_localJEC_v3.root";
output="/export/d00/scratch/tatar/output/merged_pPb_Pbp_MIX_AllQCDPhoton30_50_80_120_170_localJEC_v3";
colli=2;
./ptHatCutter.exe "${input}" $output"_ptHat_30_50.root" $colli 30 50
./ptHatCutter.exe "${input}" $output"_ptHat_50_80.root" $colli 50 80
./ptHatCutter.exe "${input}" $output"_ptHat_80_120.root" $colli 80 120
./ptHatCutter.exe "${input}" $output"_ptHat_120_9999.root" $colli 120 9999

