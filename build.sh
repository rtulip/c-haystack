#!/bin/bash

POSITIONAL_ARGS=()

while [[ $# -gt 0 ]]; do
    case $1 in
        run)
            RUN=YES
            FILE="$2"
            shift # past argument
            shift # past value
            ;;
        clean)
            CLEAN=YES
            shift # past argument
            ;;
        fullclean)
            FULLCLEAN=YES
            shift
            ;;
        -q|--quiet)
            QUIET=YES
            shift
            ;;
        -*|--*)
            echo "Unknown option $1"
            exit 1
            ;;
        *)
            POSITIONAL_ARGS+=("$1") # save positional arg
            shift # past argument
            ;;
    esac
done

set -- "${POSITIONAL_ARGS[@]}" # restore positional parameters

case ${FULLCLEAN} in
    YES)
        rm -rf .build/
        rm -rf .codegen
        rm -f main
        exit 0
        ;;
    *)
        ;;
esac

case ${CLEAN} in
    YES)
        rm -rf .build/
        rm -f main
        exit 0
        ;;
    *)
        ;;
esac

case ${QUIET} in
    YES)
        python3 scripts/build.py --quiet
        ;;
    *)
        python3 scripts/build.py
        ;;
esac

case ${RUN} in 
    YES)
        ./main ${FILE}
        ;;
    *)
        ;;
esac