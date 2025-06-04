#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <string.h>
sigjmp_buf jmpbuf;

void signal_handler(int sig) {
    const char *sig_name;
    
    switch(sig) {
        case SIGABRT: sig_name = "SIGABRT"; break;
        case SIGFPE:  sig_name = "SIGFPE";  break;
        case SIGILL:  sig_name = "SIGILL";  break;
        case SIGINT:  sig_name = "SIGINT";  break;
        case SIGSEGV: sig_name = "SIGSEGV"; break;
        case SIGTERM: sig_name = "SIGTERM"; break;
        default:      sig_name = "UNKNOWN"; break;
    }
    
    printf("\poluchen signal: %s (%d)\n", sig_name, sig);
    
    if (sig == SIGSEGV) {
        siglongjmp(jmpbuf, 1);
    }
}

void generate_segfault() {
    int *ptr = NULL;
    *ptr = 42; 
}

int main() {
    signal(SIGABRT, signal_handler);
    signal(SIGFPE,  signal_handler);
    signal(SIGILL,  signal_handler);
    signal(SIGINT,  signal_handler);
    signal(SIGSEGV, signal_handler);
    signal(SIGTERM, signal_handler);

    if (sigsetjmp(jmpbuf, 1) == 0) {
        printf("obrabotka zapushena\n");
        printf("dostupnie signali:\n");
        printf("1. SIGABRT  2. SIGFPE  3. SIGILL\n");
        printf("4. SIGINT   5. SIGSEGV 6. SIGTERM\n");
        printf("0. Exit\n");

        int choice;
        while(1) {
            printf("\nVibeirte (0-6): ");
            scanf("%d", &choice);
            
            switch(choice) {
                case 0:
                    printf("program\n");
                    exit(0);
                
                case 1:
                    printf("Ãåíåðàöèÿ SIGABRT\n");
                    abort();
                    break;
                
                case 2:
                    printf("Ãåíåðàöèÿ SIGFPE\n");
                    int a = 10, b = 0;
                    int c = a / b; // Äåëåíèå íà íîëü
                    break;
                
                case 3:
                    printf("Ãåíåðàöèÿ SIGILL\n");
                    raise(SIGILL);
                    break;
                
                case 4:
                    printf("Ãåíåðàöèÿ SIGINT\n");
                    raise(SIGINT);
                    break;
                
                case 5:
                    printf("Ãåíåðàöèÿ SIGSEGV\n");
                    generate_segfault();
                    break;
                
                case 6:
                    printf("Ãåíåðàöèÿ SIGTERM\n");
                    raise(SIGTERM);
                    break;
                
                default:
                    printf("Íåâåðíûé âûáîð!\n");
            }
        }
    }

    return 0;
}
