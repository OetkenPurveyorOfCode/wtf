#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    char* string;
    size_t len;
} StringView;

typedef struct {
    StringView* sv;
    size_t len;
    size_t cap;
} Stringvec;

void strvec_append_str(Stringvec* svec, char* str) {
    size_t len;
    for (len = 0; str[len] != '\n'&& str[len] != '\0' && len < 4095; len++) {}
    char* string = calloc(len+1, 1);
    assert(string);
    memcpy(string, str, len);
    StringView sv = {
        .string = string,
        .len = len,
    };
    if (svec->len >= svec->cap) {
        printf("realloc %s sz %zu len %zu\n", str, svec->cap, svec->len);
        svec->cap += 10000;
        svec->sv = realloc(svec->sv, sizeof(*svec->sv)*svec->cap);
        assert(svec->sv);
    }
    svec->sv[svec->len] = sv;
    svec->len += 1;
}

int main(int argc, char**argv) {
    if (argc != 2) {
        printf("Invalid argument: Usage: main.exe <filename>");
        exit(-1);
    }
    FILE* f = fopen(argv[1], "r"); // better to read entire file since we need to own strs anyway
    assert(f);
    char buf[4096];
    Stringvec dict[26] = {0};
    while (fgets(buf, sizeof(buf), f)) {
        if ('a' <= buf[0] && buf[0] <= 'z') {
            strvec_append_str(&dict[buf[0] - 'a'], buf);
        }
        else {
            printf("mope: %s", buf);
        }
    }
    fclose(f);
    FILE* of = fopen("words.h", "w+");
    fprintf(of, "typedef struct {\n");
    fprintf(of, "    char** words;\n");
    fprintf(of, "    size_t len;\n");
    fprintf(of, "} Entry;\n");
    assert(of);
    for (size_t j = 0; j < sizeof(dict)/sizeof(*dict); j++) {
        fprintf(of, "static char* words_%c[] = {\n", (char)j +'a');
        for (size_t i = 0; i < dict[j].len; i++) {
            fprintf(of, "     \"%.*s\",\n", (int)dict[j].sv[i].len, dict[j].sv[i].string);
        }
        fprintf(of, "};\n");
    }
    fprintf(of, "Entry words[] = {\n");
    for (size_t j = 0; j < sizeof(dict)/sizeof(*dict); j++) {
        fprintf(of, "    {words_%c, %zu},\n", (char)j + 'a', dict[j].len);
    }
    fprintf(of, "};\n");
    fclose(of);
}
