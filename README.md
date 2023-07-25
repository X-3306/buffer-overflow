# buffer-overflow
buffer overflow exploit

# tutorial --> https://youtu.be/33TEwVdM8GM

### wyjaśnienie ###
**0x1.0x2 kody powłoki**
W hakowaniu kod powłoki to mały fragment kodu używany jako ładunek w celu wykorzystania luki w oprogramowaniu. Nazywa się to „shellcode”, ponieważ zwykle uruchamia powłokę poleceń, z której osoba atakująca może kontrolować zaatakowaną maszynę, ale każdy fragment kodu wykonujący podobne zadanie można nazwać kodem powłoki. Kod powłoki jest zwykle zapisywany w kodzie maszynowym. (Wikipedia)

Shellcode to rodzaj ByteCode, czyli kod źródłowy w czystym kodzie maszynowym
W rzeczywistości kod powłoki to kod bajtowy, który wykonuje powłokę poleceń: "środowisko”, w którym mogę wykonywać polecenia systemowe.

Aby móc stworzyć działający Shellcode, masz (głównie) dwie możliwości:
Utwórz program asemblera, skompiluj go i połącz, a następnie wygeneruj jego kod maszynowy lub
Zrób to samo z programem C lub C++

Bardziej podstawową metodą: utwórz kod powłoki z programu asemblerowego.
Dostępnych jest wiele kodów powłoki, w wielu miejscach w Internecie. Dobrze znane miejsce jest: https://www.exploit-db.com/

Kod powłoki (.sh) który jest podany w poradniku, to bardzo prosty skrypt do kompilacji programu i wyświetlania odpowiedniego kodu bajtowego.

kod bajtowy (lub kod maszynowy) jest reprezentowany jako seria liczb szesnastkowych, które w rzeczywistości są serią lub bajtami, a dokładniej serią bitów, znaną również jako 0 i 1. Dlatego nazywa się to kodem maszynowym.
Jedynym zadaniem, które pozostało do zrobienia, jest pobranie tego kodu bajtowego i umieszczenie go w łańcuchu, jak poniżej:
`"\x48\x31\xf6\x56\x48\xbf\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x57\x54\x5f\xb0\x3b\x99\x0f\x05"`

**Testowanie kodu powłoki** (plik test.c)
Ten kod jest używany do dostarczania szablonu C do wklejania kodu powłoki i uruchamiania go na żywo z bufora znaków binarnego ELF x64. Pozwala to na globalne utworzenie bufora z kodem powłoki, a ten program oznaczy go jako RWX za pomocą funkcji mprotect()

Jak widać w komentarzach, nie używam the -z execstack w kompilacji, ponieważ wymuszam na programie traktowanie pamięci jako RWX (Read Write Execute) za pomocą mprotect().

**Uwagi**:
1. Nie możesz użyć powyższego kodu do testowania 32-bitowych kodów powłoki.

2. Ale, BArdzo łatwo jest zmienić program do testowania 32-bitowego kodu powłoki: wystarczy zmienić linię 47 z:
`void *page_offset = (void *)((long)payload_ptr & ~(getpagesize()-1));`
na:
`void *page_offset = (void *)((int)payload_ptr & ~(getpagesize()-1));`

3. Kod powłoki nie może zawierać bajtu **00 **, ponieważ program się zatrzyma. Ta funkcja powoduje jeden z największych problemów podczas tworzenia kodów powłoki. Istnieje kilka metod, których można użyć, aby uniknąć bajtu 00 (takich jak XORing) ale to jest już poza zakresem obecnego poradnika.
