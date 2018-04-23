#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int32_t n, d; // n: 分子, d: 分母
} rational;

rational reductionr(int32_t, rational*);
rational setr(int32_t, int32_t);
void printr(rational);
int32_t gcd(int32_t, int32_t);
void swap_asm2(int32_t*, int32_t*);

int32_t main(){
    rational ary[3];
    ary[0] = setr(1, 2);
    ary[1] = setr(2, 3);
    ary[2] = setr(3, 4);
    rational z = reductionr(3, ary);
    printr(z);

    return 0;
}

rational setr(int32_t n, int32_t d){
    rational z;
    if (d == 0) {
        fprintf(stderr, "Denominator␣must␣be␣nonzero.\n");
        exit(1);
    }
    z.n = n;
    z.d = d;
    return z;
}

void printr(rational z){
    printf("%d/%d\n", z.n, z.d); // -> 1/3
}

rational reductionr(int32_t n, rational *ary){
    // 加算なので分母の公倍数を取る
    int32_t denominator = 1; // 0にするとずっと0のなるので1に初期化
    for(int32_t i = 0; i < n; i++){
        denominator *= ary[i].d;
    }

    // 書く分母が倍にされた分をかけてから分子を足していく
    int32_t numerator = 0;
    for (int32_t i = 0; i < n; i++)
    {
        numerator += ary[i].n * (denominator / ary[i].d);
    }

    int32_t gcd_val = 0;
    gcd_val = gcd(numerator, denominator);

    return setr(numerator/gcd_val, denominator/gcd_val);
}

int32_t gcd(int32_t n, int32_t m){
    // n > m となるように
    if(n < m){
        swap_asm2(&n, &m);
    }
    int32_t r = 0;
    while(m != 0){
        r = n % m;
        n = m;
        m = r;
    }

    return n;
}

// スワップ用
void swap_asm2(int32_t *a, int32_t *b) {
    __asm__ __volatile{
        "mov eax, [ebx]\n\t"
        "mov ecx, [edx]\n\t"
        "xchg eax, ecx\n\t"
        "mov [ebx], eax\n\t"
        "mov [edx], ecx\n\t"
        :
        :"b"(a), "d"(b)
        :"eax", "ecx"
    };
}