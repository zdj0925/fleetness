#!/usr/bin/bash
#set -x
DATAFILE=rpclient.sh.data
list ()
{
    while IFS='|' read -r col1 col2 col3; do
            printf "%s\t%s\t%s\n" "$col1" "$col2" "$col3" 
    done < $DATAFILE
}
senddata() {
    while IFS='|' read -r col1 col2 col3; do
        if [ "$col1"x = "$1"x ]; then
            printf "sending: \n%s\n" "$col3"
            printf "response: \n"
            printf "%s" "$col3" | nc 127.0.0.1 1234
            if [[ "${col2%% *}"x = "exit"x ]]; then
                printf "exiting\n"
                exit
            fi
            break
        fi
    done < $DATAFILE
}

main ()
{
    while true
    do
        list
        read -p "Enter a number: " num
        senddata $num
        
    done

}
main
