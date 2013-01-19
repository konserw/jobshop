    kSzereg - program szeregujący zadania w systemie wytwarzania gniazdowego 
    z wykorzystaniem heurystyk LIFO i FIFO, oraz wyznaczający parametry
    strategii Just in Time. Praca inżynierska na wydziale Automatyki,
    Elektroniki i Informatyki Politechniki Śląskiej w Gliwicach.
    Copyright (C) 2012  Kamil 'konserw' Strzempowicz, konserw@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


Program kSzereg został napisany w C++ na potrzeby pracy dyplomowej.
Umożliwia on przeprowadzenie szeregowania zadań w systemie wytwarzania gniaz-
dowego na podstawie heurystyki FIFO bądź LIFO. Wprowadzanie danych odbywa
się za pośrednictwem graficznego interface’u opartego o framework Qt. Na górnej
belce programu po prawej stronie znajdują się kontrolki umożliwiające wybór heu-
rystyki używanej do rozwiązania zadania oraz parametrów α, β podstawianych do
wzoru (2). Znajdują się tam też przyciski umożliwiające zapisanie zlecenia do pliku
binarnego z rozszerzeniem .mar (eksport) oraz wczytanie zlecenia z takiego pliku
(import).
Przed dodaniem zadań do zlecenia należy ustalić maksymalną długość marszruty.
W zadaniach z krótszą marszrutą technologiczną należy pozostawić operacje z ze-
rowym czasem, które nie będą brane pod uwagę podczas rozwiązywania JSSP. Po
dodaniu zadania możliwość zmiany długości marszruty jest blokowana. Każda ope-
racja jest definiowana przez numer maszyny, na której ma zostać wykonana oraz czas
jej wykonywania. Ilość maszyn możliwych do wyboru może być zmieniana w czasie
edycji zlecenia (po dodaniu zadań). Poza marszrutą technologiczną zadanie definiują
czasy rozpoczęcia (rj ) i zakończenia (dj ) zadania. Możliwe jest też nadanie zadaniu
nazwy.
Program kSzereg rezentuje wyniki działania w postaci wykresu Gantt’a wraz
z tabelą zawierającą czasy wykonania (Cj ), przepływu (fj ), spóźnienia (lj ) i przed-
wczesności (earliness, ej ) każdego zadania zlecenia. Dodatkowo prezentowane są wy-
znaczniki jakości uszeregowania zlecenia jako cołości: czas ukończenia całego zlecenia
(Cmax ), średni czas przepływu (F ), maksymalne spóźnienie (Tmax ), średnie spóźnie-
nie (T ) oraz wartości funkcji kosztów (1) oraz (2).
Z poziomu okna wyznaczonego uszeregowania istnieje możliwość zapisania wy-
ników działania programu w postaci pliku .tex z kodem w L TEX-u lub .pdf. W obu
przypadkach sam wykres Gantt’a jest eksportowany do pliku .svg w folderze out-
put. Funkcje te korzystają z zewnętrznych programów inkscape oraz rubber (wraz
z odpowiednimi paczkami texlive), które muszą być zainstalowane w systemie.
Dodatkowo istnieje możliwość obsługi programu kSzereg z poziomu terminalu
tekstowego korzystając z wcześniej zapisanych plików .mar, nie jest bowiem moż-
liwa konfiguracja zadania jedynie, rozwiązanie problemu i eksport wyników do pliku
.tex lub .pdf. Zaletą obsługi programu z termianlu jest możliwość podania jako para-
metr nazwy pliku tekstowego z zapisanymi ścieżkami dostępu do wielu plików .mar,
a nawet wybranie obu heurystyk do rozwiązania tych zleceń, co spowoduje rozwią-
zanie JSSP dla każdego z tych zadań. Szczegółowy opis intreface’u linii poleceń jest
dostępny po uruchomieniu programu z przełącznikiem ’–help’.



