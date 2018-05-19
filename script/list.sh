#!/bin/sh
MODULE_LIST=("FEP" "BEP" "DIAMETER" "TCAP");
FEP=("1002|3004@10.12.11.11" "2900@10.22.22.22" "2901@10.11.11.11");
BEP=("23@10.33.33.33", "34|35@10.2.2.2");
TCAP=("TCAP1", "TCAP2");

config_rule(){
for module in ${MODULE_LIST[@]}; do
    echo $module
    #echo ${{$module}[0]}
    #echo ${FEP[0]}
    if [ $module == "FEP" ]; then
        #echo $module >> config.rule
        echo ${FEP[@]}
        config_TA ${FEP[@]}
    fi    
done
}

config_TA(){
OLD_IFS="$IFS"
#IFS="|"
#for configure in ${FEP[@]}; do
for configure in $@; do ##
    #echo $configure | awk '{print $1}' #split by space' '
    echo "configure $configure"
    IFS="@"
    arry=($configure)
    ip=${arry[1]}
    ports=${arry[0]}
    echo "IP $ip  ports $ports"
    IFS="|"
    for port in ${ports[@]}; do
        echo $port
        echo $port"@"$ip #write to config.TA
    done
    #IFS="$OLD_IFS"
done
IFS="$OLD_IFS"
}
#config_TA
config_rule
