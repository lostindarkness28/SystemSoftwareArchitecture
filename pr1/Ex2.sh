#!/bin/bash

LIB_PATH="/lib/x86_64-linux-gnu/libm.so.6"

echo "--- Аналіз бібліотеки $LIB_PATH ---"
FUNCTIONS=("sin" "cos" "exp")
for FUNC in "${FUNCTIONS[@]}"; do
    echo "Пошук функції: $FUNC..."
    nm -D "$LIB_PATH" | grep -w "$FUNC"
done

echo "--- Пошук завершено ---"
