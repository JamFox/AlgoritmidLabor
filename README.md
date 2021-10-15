# IAS0090 Algoritmid ja andmestruktuurid / Algorithms and Data Structures Lab

Struct 7, Object 4

http://www.tud.ttu.ee/im/Viktor.Leppikson/

# Linuxil Visual Studio Compiler (Credit to: rebane@alkohol.ee)

Esmalt on vaja windowsi masinat või virtuaalmasinat. Ning sinna tuleb installida Microsoft Visual Studio 2019. Kiire sissejuhatus on Viktor Leppiksoni enda dokumendis: http://www.tud.ttu.ee/im/Viktor.Leppikson/IAS0090%20labori%20juhend%202021.pdf

Seal lk 5 all on viide, kust saab seda tasuta Community versiooni tõmmata. Ma just selle tõmbasingi.

Kui nüüd seda Visual Studiot windowsis installida, siis tuli vist kuskil teha ka linnuke, et tahad lisaks installida windowsi jaoks C++ vahendeid. Ilma nendeta ei saa, aga seda ei ole Leppiksonil mainitud.

Igatahes kui see kõik on installitud, siis tuleb windowsist kopeerida kaks kataloogi linuxisse nii et wine neid kasutada saaks. Mina pakkisin need zipiga kokku ja kopeerisin linuxisse scp'ga. Windowsi kataloogid on järgmised:
- C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC
- C:\Program Files (x86)\Windows Kits\10

Üldiselt kui wine on installitud, siis vaikimisi on C ketas windowsis igal kasutajal asukohas: ~/.wine/drive_c

Et segadusi vältida, siis ma kopeerisin nii, et need kataloogid asuvad wine seisukohast täpselt samas kohas kus nad on windosis. Seega tekkisid linuxisse kataloogid:
- ~/.wine/drive_c/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC
- ~/.wine/drive_c/Program Files (x86)/Windows Kits/10

Wine enda installisin linuxi oma vahenditega. Minu puhul siis debian ja "apt-get install wine".

Järgnevalt on vaja tekitada omale linuxisse projekti kataloog. IAS0090 labori kompileerimiseks on vaja veel Leppiksoni lehelt http://www.tud.ttu.ee/im/Viktor.Leppikson/IAS0090%20labori%20failid.zip

Selguse huvides paigutasin mina need failid eraldi ./lib/ kataloogi projektikataloogis.

Nüüd üldiselt peaks saama juba näidet kompileerida. Panin oma "template" projektikataloogi pakituna hetkel sinna üles: http://rebane.alkohol.ee/stuff/lab.tar.gz

Seal sees on Makefile, main.cpp ja Leppiksoni library. Lisaks on  tarvis paari .dll faili windowsi kataloogidest, et valmis kompileeritud main.exe wine'ga käivituks. Mina kopeerisin need lihtsalt projektikataloogi. Need failid on samuti arhiiviga kaasas, aga võimalik et kui on Visual Studiost mingi teine versioon, siis tuleb ikka ise kopeerida. Need failid on:
- ~/.wine/drive_c/Program Files (x86)/Windows Kits/10/bin/10.0.19041.0/x86/ucrt/ucrtbased.dll
- ~/.wine/drive_c/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Redist/MSVC/14.29.30133/debug_nonredist/x86/Microsoft.VC142.DebugCRT/vcruntime140d.dll

Lisaks tegin ma omale veel ./a.out nimelise väikse skripti, mis ei tee muud kui käivitab wine abiga main.exe. Lihtsalt harjumus on linuxis kirjutada pärast kompileerimist "./a.out", mitte "wine main.exe". Aga tegin Makefile'sse ka aliase "make run" või "make install". Jällegi harjumuse pärast.

Aga kui see kõik on tehtud, siis:
1) vim main.cpp
2) make
3) make run
