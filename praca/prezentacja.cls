%Moja paczka do strony tutułowej dla inżynierki

\NeedsTeXFormat{LaTeX2e}[1995/12/01]
\ProvidesClass{prezentacja}
              [2013/01/20
 nonStandard LaTeX presentation class]
\LoadClass[compress]{beamer}

\RequirePackage[polish]{babel}
\RequirePackage[utf8]{inputenc}
\RequirePackage[OT4]{fontenc}
\RequirePackage{datetime}
\RequirePackage[labelformat=empty]{caption}
%\RequirePackage[section]{placeins}



\setbeamertemplate{frametitle}
{ 
    \scshape
    \insertframetitle 
    \par 
}

\def\today{\ifcase\month\or styczeń\or luty\or marzec\or kwiecień\or maj\or czerwiec\or lipec\or sierpień\or wrzesień\or październik\or listopad\or grudzień\fi \space\number\year}

\newcommand{\fontnag}{\scshape}
\newcommand{\fonttyt}{\small}
\newcommand{\fontpromotor}{\footnotesize}
\newcommand{\fontautor}{\footnotesize}
\newcommand{\fontautoretyk}{\footnotesize}
\newcommand{\fontpromotoretyk}{\footnotesize}
\newcommand{\fontrodzpracy}{\footnotesize}
\newcommand{\fontmiasto}{\scriptsize}

\def\promotor#1{\gdef\@promotor{#1}}
\def\title#1{\gdef\@title{#1}}
\def\autor#1{\gdef\@autor{#1}}
\def\rodzPracy#1{\gdef\@rodzPracy{#1}}
\def\kierunek#1{\gdef\@kierunek{#1}}

\def\StronaTyt{\thispagestyle{empty}
    \logo
    \GornaczescSytronyTyT
    \wypisRodzajuPracy
    \wypisanieTyt
    \wypisanieAutorPromotor
    \dolnaczescStronyTyt
}

\def\logo{
    \begin{figure}[th]
    \centering
    \includegraphics[width=50px, keepaspectratio=true]{./polsl}
    \end{figure}
}

\def\GornaczescSytronyTyT{%
         \begin{center}\fontnag
         Politechnika \'Sl\k aska\\
         Wydzia\l\ Automatyki, Elektroniki i Informatyki\\
         Kierunek \@kierunek
      \end{center}\par
      }

\def\wypisanieTyt{\begin{center}\fonttyt
\@title
\end{center}
}

\def\wypisRodzajuPracy{\begin{center}{\fontrodzpracy
\@rodzPracy}\end{center}}

\def\wypisanieAutorPromotor{
    {\fontautoretyk Autor: }{\fontautor \@autor} \\
    {\fontpromotoretyk Kierujący pracą: }{\fontpromotor \@promotor} 
}

\def\dolnaczescStronyTyt{%
    \begin{center}
   {\fontmiasto Gliwice, \today }
     \end{center}\par\break
}


\endinput
%%
%% End of file `stronaTyt.sty'.
