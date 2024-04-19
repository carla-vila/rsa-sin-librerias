#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

int main() {
    const char* number_str = "1232663856125588687434661844748248537607032756283820193330891679454319646054938919637037805552264427973970252604248734268646061562545490354747125697705834311020677999431630114868193862092727832110639773191903682889441952971015475996569712520630371143533464190192167277413302666026173676557602552365526639943554424303044717518077189805930413771674706770460329522933426941362890328247761964355673083536571273735218319569731179160421634555393152700820206471676467706134292085407619453";
    uint64_t m[20] = {0};
    int array_size = sizeof(m) / sizeof(m[0]);

    int len = strlen(number_str);
    int num_words = 0;
    char temp[20];

    while (len > 0 && num_words < array_size) {
        int take = len > 18 ? 18 : len;
        strncpy(temp, number_str + (len - take), take);
        temp[take] = '\0';
        m[num_words++] = strtoull(temp, NULL, 10);
        len -= take;
    }

    printf("uint64_t m[%d] = {", array_size);
    for (int i = 0; i < array_size; i++) {
        printf("0x%016llx", m[i]);
        if (i < array_size - 1) printf(", ");
    }
    printf("};\n");

    return 0;
}