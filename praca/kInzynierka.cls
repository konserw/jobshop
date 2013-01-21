%% \CharacterTable
%%  {Upper-case    \A\B\C\D\E\F\G\H\I\J\K\L\M\N\O\P\Q\R\S\T\U\V\W\X\Y\Z
%%   Lower-case    \a\b\c\d\e\f\g\h\i\j\k\l\m\n\o\p\q\r\s\t\u\v\w\x\y\z
%%   Digits        \0\1\2\3\4\5\6\7\8\9
%%   Exclamation   \!     Double quote  \"     Hash (number) \#
%%   Dollar        \$     Percent       \%     Ampersand     \&
%%   Acute accent  \'     Left paren    \(     Right paren   \)
%%   Asterisk      \*     Plus          \+     Comma         \,
%%   Minus         \-     Point         \.     Solidus       \/
%%   Colon         \:     Semicolon     \;     Less than     \<
%%   Equals        \=     Greater than  \>     Question mark \?
%%   Commercial at \@     Left bracket  \[     Backslash     \\
%%   Right bracket \]     Circumflex    \^     Underscore    \_
%%   Grave accent  \`     Left brace    \{     Vertical bar  \|
%%   Right brace   \}     Tilde         \~}

\NeedsTeXFormat{LaTeX2e}[1995/12/01]
\ProvidesClass{kInzynierka}
    [2013/01/20
    nonStandard LaTeX document class]
        
\RequirePackage[polish]{babel}
\RequirePackage[utf8]{inputenc}
\RequirePackage[OT4]{fontenc}
\RequirePackage{mathtools}
\RequirePackage[section]{placeins}
\RequirePackage[justification=raggedright,singlelinecheck=false,labelsep=period]{caption}
\RequirePackage{datetime}
\RequirePackage{bold-extra}

\def\miech{\ifcase\month\or styczeń\or luty\or marzec\or kwiecień\or maj\or czerwiec\or lipec\or sierpień\or wrzesień\or październik\or listopad\or grudzień\fi \space\number\year}    

\newcommand\@ptsize{}
\newif\if@restonecol
\newif\if@titlepage
\@titlepagefalse

\def\refstepcounter#1{\stepcounter{#1}%
    \protected@edef\@currentlabel
       {\csname p@#1\endcsname\csname the#1\endcsname\protect}%
}


\let\rodzajKodow\relax
\DeclareOption{dos}     {\def\rodzajKodow{\RequirePackage[cp852]{inputenc}}}
\DeclareOption{win}     {\def\rodzajKodow{\RequirePackage[cp1250]{inputenc}}}

\if@compatibility
  \renewcommand\@ptsize{0}
\else
\DeclareOption{10pt}{\renewcommand\@ptsize{0}}
\fi
\DeclareOption{11pt}{\renewcommand\@ptsize{1}}
\DeclareOption{12pt}{\renewcommand\@ptsize{2}}
\if@compatibility\else
%\DeclareOption{oneside}{\@twosidefalse \@mparswitchfalse}
\fi
\DeclareOption{twoside}{\@twosidetrue  \@mparswitchtrue}
\DeclareOption{draft}{\setlength\overfullrule{5pt}}
\if@compatibility\else
\DeclareOption{final}{\setlength\overfullrule{0pt}}
\fi
\DeclareOption{titlepage}{\@titlepagetrue}
\if@compatibility\else
\DeclareOption{notitlepage}{\@titlepagefalse}
\fi
\if@compatibility\else
\DeclareOption{onecolumn}{\@twocolumnfalse}
\fi
\DeclareOption{twocolumn}{\@twocolumntrue}

\DeclareOption{leqno}{\input{leqno.clo}}
\DeclareOption{fleqn}{\input{fleqn.clo}}
\DeclareOption{openbib}{
  \AtEndOfPackage{
   \renewcommand\@openbib@code{
      \advance\leftmargin\bibindent
      \itemindent -\bibindent
      \listparindent \itemindent
      \parsep \z@
      }
   \renewcommand\newblock{\par}}
}

\ExecuteOptions{a4paper,12pt,twoside,onecolumn,final}
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
\ProcessOptions
\input{size1\@ptsize.clo}
\setlength\lineskip{1\p@}
\setlength\normallineskip{1\p@}
\renewcommand\baselinestretch{1.2}
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
\setlength\parskip{0\p@ \@plus \p@}
\@lowpenalty   51
\@medpenalty  151
\@highpenalty 301
\setcounter{topnumber}{2}
\renewcommand\topfraction{.7}
\setcounter{bottomnumber}{1}
\renewcommand\bottomfraction{.3}
\setcounter{totalnumber}{3}
\renewcommand\textfraction{.2}
\renewcommand\floatpagefraction{.5}
\setcounter{dbltopnumber}{2}
\renewcommand\dbltopfraction{.7}
\renewcommand\dblfloatpagefraction{.5}
\if@twoside
  \def\ps@headings{%
      \let\@oddfoot\@empty\let\@evenfoot\@empty
      \def\@evenhead{\thepage\hfil\slshape\leftmark}%
      \def\@oddhead{{\slshape\rightmark}\hfil\thepage}%
      \let\@mkboth\markboth
    \def\sectionmark##1{%
      \markboth {\MakeUppercase{%
        \ifnum \c@secnumdepth >\z@
          \thesection\quad
        \fi
        ##1}}{}}%
    \def\subsectionmark##1{%
      \markright {%
        \ifnum \c@secnumdepth >\@ne
          \thesubsection\quad
        \fi
        ##1}}}
\else
  \def\ps@headings{%
    \let\@oddfoot\@empty
    \def\@oddhead{{\slshape\rightmark}\hfil\thepage}%
    \let\@mkboth\markboth
    \def\sectionmark##1{%
      \markright {\MakeUppercase{%
        \ifnum \c@secnumdepth >\m@ne
          \thesection\quad
        \fi
        ##1}}}}
\fi

\def\ps@myheadings{%
    \let\@oddfoot\@empty\let\@evenfoot\@empty
    \def\@evenhead{\thepage\hfil\slshape\leftmark}%
    \def\@oddhead{{\slshape\rightmark}\hfil\thepage}%
    \let\@mkboth\@gobbletwo
    \let\sectionmark\@gobble
    \let\subsectionmark\@gobble
    }
  \if@titlepage
  \newcommand\maketitle{\begin{titlepage}%
  \let\footnotesize\small
  \let\footnoterule\relax
  \let \footnote \thanks
  \null\vfil
  \vskip 60\p@
  \begin{center}%
    {\LARGE \@title \par}%
    \vskip 3em%
    {\large
     \lineskip .75em%
      \begin{tabular}[t]{c}%
        \@author
      \end{tabular}\par}%
      \vskip 1.5em%
    {\large \@date \par}%       % Set date in \large size.
  \end{center}\par
  \@thanks
  \vfil\null
  \end{titlepage}%
  \setcounter{footnote}{0}%
  \global\let\thanks\relax
  \global\let\maketitle\relax
  \global\let\@thanks\@empty
  \global\let\@author\@empty
  \global\let\@date\@empty
  \global\let\@title\@empty
  \global\let\title\relax
  \global\let\author\relax
  \global\let\date\relax
  \global\let\and\relax
}
\else
\newcommand\maketitle{\par
  \begingroup
    \renewcommand\thefootnote{\@fnsymbol\c@footnote}%
    \def\@makefnmark{\rlap{\@textsuperscript{\normalfont\@thefnmark}}}%
    \long\def\@makefntext##1{\parindent 1em\noindent
            \hb@xt@1.8em{%
                \hss\@textsuperscript{\normalfont\@thefnmark}}##1}%
    \if@twocolumn
      \ifnum \col@number=\@ne
        \@maketitle
      \else
        \twocolumn[\@maketitle]%
      \fi
    \else
      \newpage
      \global\@topnum\z@   % Prevents figures from going at top of page.
      \@maketitle
    \fi
    \thispagestyle{plain}\@thanks
  \endgroup
  \setcounter{footnote}{0}%
  \global\let\thanks\relax
  \global\let\maketitle\relax
  \global\let\@maketitle\relax
  \global\let\@thanks\@empty
  \global\let\@author\@empty
  \global\let\@date\@empty
  \global\let\@title\@empty
  \global\let\title\relax
  \global\let\author\relax
  \global\let\date\relax
  \global\let\and\relax
}
\def\@maketitle{%
  \newpage
  \null
  \vskip 2em%
  \begin{center}%
  \let \footnote \thanks
    {\LARGE \@title \par}%
    \vskip 1.5em%
    {\large
      \lineskip .5em%
      \begin{tabular}[t]{c}%
        \@author
      \end{tabular}\par}%
    \vskip 1em%
    {\large \@date}%
  \end{center}%
  \par
  \vskip 1.5em}
\fi
\setcounter{secnumdepth}{3}
\newcounter {part}
\newcounter {section}
\newcounter {subsection}[section]
\newcounter {subsubsection}[subsection]
\newcounter {paragraph}[subsubsection]
\newcounter {subparagraph}[paragraph]
\renewcommand \thepart {\@Roman\c@part}
\renewcommand \thesection {\@arabic\c@section}
\renewcommand\thesubsection   {\thesection.\@arabic\c@subsection}
\renewcommand\thesubsubsection{\thesubsection .\@arabic\c@subsubsection}
\renewcommand\theparagraph    {\thesubsubsection.\@arabic\c@paragraph}
\renewcommand\thesubparagraph {\theparagraph.\@arabic\c@subparagraph}
\newcommand\part{%
   \if@noskipsec \leavevmode \fi
   \par
   \addvspace{4ex}%
   \@afterindentfalse
   \secdef\@part\@spart}

\def\@part[#1]#2{%
    \ifnum \c@secnumdepth >\m@ne
      \refstepcounter{part}%
      \addcontentsline{toc}{part}{\thepart\hspace{1em}#1}%
    \else
      \addcontentsline{toc}{part}{#1}%
    \fi
    {\parindent \z@ \raggedright
     \interlinepenalty \@M
     \normalfont
     \ifnum \c@secnumdepth >\m@ne
       \Large\bfseries \partname~\thepart
       \par\nobreak
     \fi
     \huge \bfseries #2%
     \markboth{}{}\par}%
    \nobreak
    \vskip 3ex
    \@afterheading}
\def\@spart#1{%
    {\parindent \z@ \raggedright
     \interlinepenalty \@M
     \normalfont
     \huge \bfseries #1\par}%
     \nobreak
     \vskip 3ex
     \@afterheading}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\newcommand\section{\@startsection {section}{1}{\z@}%
                                   {3.5ex \@plus 1ex \@minus .2ex}%
                                   {10.3ex \@plus 1.2ex}%
                                   {\normalfont\LARGE\bfseries\sffamily}}
\newcommand\subsection{\@startsection{subsection}{2}{\z@}%
                                     {3.25ex\@plus 1ex \@minus .2ex}%
                                     {2.5ex \@plus .6ex}%
                                     {\normalfont\large\bfseries\sffamily}}
\newcommand\subsubsection{\@startsection{subsubsection}{3}{\z@}%
                                     {2.25ex\@plus 1ex \@minus .2ex}%
                                     {1.0ex \@plus .3ex}%
                                     {\normalfont\normalsize\bfseries\sffamily}}
\newcommand\paragraph{\@startsection{paragraph}{4}{\z@}%
                                    {3.25ex \@plus1ex \@minus.2ex}%
                                    {-1em}%
                                    {\normalfont\normalsize\bfseries}}
\newcommand\subparagraph{\@startsection{subparagraph}{5}{\parindent}%
                                       {3.25ex \@plus1ex \@minus .2ex}%
                                       {-1em}%
                                      {\normalfont\normalsize\bfseries}}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\let\subsectionXX=\subsection
\def\subsection{\par\PrzedSubSection\PrzedSubSectionx
\vskip0pt plus4ex \goodbreak\vskip0pt plus-4ex\relax
\subsectionXX}
\let\subsubsectionXX=\subsubsection
\def\subsubsection{\par
\vskip0pt plus4ex \goodbreak\vskip0pt plus-4ex\relax
\subsubsectionXX}

\let\sectionXX=\section
\def\section{\@ifnextchar*{\sectionAA}{\sectionBB}}

\def\sectionAA{\newoddpage 
      \thispagestyle{empty}%
       \sectionXX
       }

\def\sectionBB{\newoddpage
     \PrzedSection
     \PrzedSectionx
      \thispagestyle{empty}%
       \sectionXX
       }

\if@twocolumn
  \setlength\leftmargini  {2em}
\else
  \setlength\leftmargini  {2.5em}
\fi
\leftmargin  \leftmargini
\setlength\leftmarginii  {2.2em}
\setlength\leftmarginiii {1.87em}
\setlength\leftmarginiv  {1.7em}
\if@twocolumn
  \setlength\leftmarginv  {.5em}
  \setlength\leftmarginvi {.5em}
\else
  \setlength\leftmarginv  {1em}
  \setlength\leftmarginvi {1em}
\fi
\setlength  \labelsep  {.5em}
\setlength  \labelwidth{\leftmargini}
\addtolength\labelwidth{-\labelsep}
\@beginparpenalty -\@lowpenalty
\@endparpenalty   -\@lowpenalty
\@itempenalty     -\@lowpenalty
\renewcommand\theenumi{\@arabic\c@enumi}
\renewcommand\theenumii{\@alph\c@enumii}
\renewcommand\theenumiii{\@roman\c@enumiii}
\renewcommand\theenumiv{\@Alph\c@enumiv}
\newcommand\labelenumi{\theenumi.}
\newcommand\labelenumii{(\theenumii)}
\newcommand\labelenumiii{\theenumiii.}
\newcommand\labelenumiv{\theenumiv.}
\renewcommand\p@enumii{\theenumi}
\renewcommand\p@enumiii{\theenumi(\theenumii)}
\renewcommand\p@enumiv{\p@enumiii\theenumiii}
\newcommand\labelitemi{\textbullet}
\newcommand\labelitemii{\normalfont\bfseries \textendash}
\newcommand\labelitemiii{\textasteriskcentered}
\newcommand\labelitemiv{\textperiodcentered}
\newenvironment{description}
               {\list{}{\labelwidth\z@ \itemindent-\leftmargin
                        \let\makelabel\descriptionlabel}}
               {\endlist}
\newcommand*\descriptionlabel[1]{\hspace\labelsep
                                \normalfont\bfseries #1}
\if@titlepage
  \newenvironment{abstract}{%
      \titlepage
      \null\vfil
      \@beginparpenalty\@lowpenalty
      \begin{center}%
        \bfseries \abstractname
        \@endparpenalty\@M
      \end{center}}%
     {\par\vfil\null\endtitlepage}
\else
  \newenvironment{abstract}{%
      \if@twocolumn
        \section*{\abstractname}%
      \else
        \small
        \begin{center}%
          {\bfseries \abstractname\vspace{-.5em}\vspace{\z@}}%
        \end{center}%
        \quotation
      \fi}
      {\if@twocolumn\else\endquotation\fi}
\fi
\newenvironment{verse}
               {\let\\\@centercr
                \list{}{\itemsep      \z@
                        \itemindent   -1.5em%
                        \listparindent\itemindent
                        \rightmargin  \leftmargin
                        \advance\leftmargin 1.5em}%
                \item\relax}
               {\endlist}
\newenvironment{quotation}
               {\list{}{\listparindent 1.5em%
                        \itemindent    \listparindent
                        \rightmargin   \leftmargin
                        \parsep        \z@ \@plus\p@}%
                \item\relax}
               {\endlist}
\newenvironment{quote}
               {\list{}{\rightmargin\leftmargin}%
                \item\relax}
               {\endlist}
\if@compatibility
\newenvironment{titlepage}
    {%
      \if@twocolumn
        \@restonecoltrue\onecolumn
      \else
        \@restonecolfalse\newpage
      \fi
      \thispagestyle{empty}%
      \setcounter{page}\z@
    }%
    {\if@restonecol\twocolumn \else \newpage \fi
    }
\else
\newenvironment{titlepage}
    {%
      \if@twocolumn
        \@restonecoltrue\onecolumn
      \else
        \@restonecolfalse\newpage
      \fi
      \thispagestyle{empty}%
      \setcounter{page}\@ne
    }%
    {\if@restonecol\twocolumn \else \newpage \fi
     \if@twoside\else
        \setcounter{page}\@ne
     \fi
    }
\fi
\newcommand\appendix{\par
  \setcounter{section}{0}%
  \setcounter{subsection}{0}%
  \gdef\thesection{\@Alph\c@section}}
\setlength\arraycolsep{5\p@}
\setlength\tabcolsep{6\p@}
\setlength\arrayrulewidth{.4\p@}
\setlength\doublerulesep{2\p@}
\setlength\tabbingsep{\labelsep}
\skip\@mpfootins = \skip\footins
\setlength\fboxsep{3\p@}
\setlength\fboxrule{.4\p@}
\renewcommand \theequation {\@arabic\c@equation}
\newcounter{figure}
\renewcommand \thefigure {\@arabic\c@figure}
\def\fps@figure{tbp}
\def\ftype@figure{1}
\def\ext@figure{lof}
\def\fnum@figure{\figurename~\thefigure}
\newenvironment{figure}
               {\@float{figure}}
               {\end@float}
\newenvironment{figure*}
               {\@dblfloat{figure}}
               {\end@dblfloat}
\newcounter{table}
\renewcommand\thetable{\@arabic\c@table}
\def\fps@table{tbp}
\def\ftype@table{2}
\def\ext@table{lot}
\def\fnum@table{\tablename~\thetable}
\newenvironment{table}
               {\@float{table}}
               {\end@float}
\newenvironment{table*}
               {\@dblfloat{table}}
               {\end@dblfloat}
%\newlength\abovecaptionskip
%\newlength\belowcaptionskip
\setlength\abovecaptionskip{10\p@}
\setlength\belowcaptionskip{0\p@}

 \newdimen\capspecdimx  
\long\def\@makecaption#1#2{%
  \vskip\abovecaptionskip
  \setbox0=\hbox{#1: }%
 \capspecdimx=\wd0 
  \sbox\@tempboxa{#1: #2}%
  \ifdim \wd\@tempboxa >\hsize
    #1: #2\par
  \else
    \global \@minipagefalse
    \ifdim \wd\@tempboxa >\capspecdimx
    \hb@xt@\hsize{\hfil\box\@tempboxa\hfil}%
    \else
    \hb@xt@\hsize{\hfil#1.\hfil}%
    \fi
  \fi
  \vskip\belowcaptionskip}

\DeclareOldFontCommand{\rm}{\normalfont\rmfamily}{\mathrm}
\DeclareOldFontCommand{\sf}{\normalfont\sffamily}{\mathsf}
\DeclareOldFontCommand{\tt}{\normalfont\ttfamily}{\mathtt}
\DeclareOldFontCommand{\bf}{\normalfont\bfseries}{\mathbf}
\DeclareOldFontCommand{\it}{\normalfont\itshape}{\mathit}
\DeclareOldFontCommand{\sl}{\normalfont\slshape}{\@nomath\sl}
\DeclareOldFontCommand{\sc}{\normalfont\scshape}{\@nomath\sc}
\DeclareRobustCommand*\cal{\@fontswitch\relax\mathcal}
\DeclareRobustCommand*\mit{\@fontswitch\relax\mathnormal}
\newcommand\@pnumwidth{1.55em}
\newcommand\@tocrmarg{2.55em}
\newcommand\@dotsep{4.5}
\setcounter{tocdepth}{3}
\newcommand\tableofcontents{%
    \section*{\contentsname
        \@mkboth{%
           \MakeUppercase\contentsname}{\MakeUppercase\contentsname}}%
    \@starttoc{toc}%
    }
\newcommand*\l@part[2]{%
  \ifnum \c@tocdepth >-2\relax
    \addpenalty\@secpenalty
    \addvspace{2.25em \@plus\p@}%
    \begingroup
      \parindent \z@ \rightskip \@pnumwidth
      \parfillskip -\@pnumwidth
      {\leavevmode
       \large \bfseries #1\hfil \hb@xt@\@pnumwidth{\hss #2}}\par
       \nobreak
       \if@compatibility
         \global\@nobreaktrue
         \everypar{\global\@nobreakfalse\everypar{}}%
      \fi
    \endgroup
  \fi}
\newcommand*\l@section[2]{%
  \ifnum \c@tocdepth >\z@
    \addpenalty\@secpenalty
    \addvspace{1.0em \@plus\p@}%
    \setlength\@tempdima{1.8em}%
    \begingroup
      \parindent \z@ \rightskip \@pnumwidth
      \parfillskip -\@pnumwidth
      \leavevmode \bfseries
      \advance\leftskip\@tempdima
      \hskip -\leftskip
      #1\nobreak\hfil \nobreak\hb@xt@\@pnumwidth{\hss #2}\par
    \endgroup
  \fi}

\newcommand*\l@subsection{\@dottedtocline{2}{1.5em}{2.8em}}
\newcommand*\l@subsubsection{\@dottedtocline{3}{3.8em}{4.2em}}
\newcommand*\l@paragraph{\@dottedtocline{4}{7.0em}{4.1em}}
\newcommand*\l@subparagraph{\@dottedtocline{5}{10em}{5em}}
\newcommand\listoffigures{%
    \section*{\listfigurename
      \@mkboth{\MakeUppercase\listfigurename}%
              {\MakeUppercase\listfigurename}}%
    \@starttoc{lof}%
    }
\newcommand*\l@figure{\@dottedtocline{1}{1.5em}{2.3em}}
\newcommand\listoftables{%
    \section*{\listtablename
      \@mkboth{%
          \MakeUppercase\listtablename}{\MakeUppercase\listtablename}}%
    \@starttoc{lot}%
    }
\let\l@table\l@figure
\newdimen\bibindent
\setlength\bibindent{1.5em}

%zmiana bibliografii na 'zwykly' rozdzial
\newenvironment{thebibliography}[1]
     {\section{\refname}
 %       \markboth{\MakeUppercase\refname\liniaA}{\liniaB\MakeUppercase\refname}%
 %       \@mkboth{\MakeUppercase\refname}{\MakeUppercase\refname}}%
 %        \addcontentsline{toc}{section}{\refname}%
      \list{\@biblabel{\@arabic\c@enumiv}}%
           {\settowidth\labelwidth{\@biblabel{#1}}%
            \leftmargin\labelwidth
            \advance\leftmargin\labelsep
            \@openbib@code
            \usecounter{enumiv}%
            \let\p@enumiv\@empty
            \renewcommand\theenumiv{\@arabic\c@enumiv}}%
      \sloppy
      \clubpenalty4000
      \@clubpenalty \clubpenalty
      \widowpenalty4000%
      \sfcode`\.\@m}
     {\def\@noitemerr
       {\@latex@warning{Empty `thebibliography' environment}}%
      \endlist}


%%% do test¢w \twocolumn
\def \twocolumn {%
  \clearpage
  \global\columnwidth\textwidth
  \global\advance\columnwidth-\columnsep
  \global\divide\columnwidth\tw@
  \global\hsize\columnwidth
  \global\linewidth\columnwidth
  \global\@twocolumntrue
  \global\@firstcolumntrue
  \col@number \tw@
  \@ifnextchar [\@topnewpage\@floatplacement
}



\newcommand\newblock{\hskip .11em\@plus.33em\@minus.07em}
\let\@openbib@code\@empty
\newenvironment{theindex}
               {\if@twocolumn
                  \@restonecolfalse
                \else
                  \@restonecoltrue
                \fi
                \columnseprule \z@
                \columnsep 35\p@
                \twocolumn[\section*{\indexnameY}]
                \markboth{\MakeUppercase\indexnameX\liniaA}
                        {\liniaB\MakeUppercase\indexnameX}
                \@mkboth{\MakeUppercase\indexname}
                        {\MakeUppercase\indexname}
                \thispagestyle{empty}\parindent\z@
                \parskip\z@ \@plus .3\p@\relax
                \let\item\@idxitem}
               {\if@restonecol\onecolumn\else\clearpage\fi}
\newcommand\@idxitem{\par\hangindent 40\p@}
\newcommand\subitem{\@idxitem \hspace*{20\p@}}
\newcommand\subsubitem{\@idxitem \hspace*{30\p@}}
\newcommand\indexspace{\par \vskip 10\p@ \@plus5\p@ \@minus3\p@\relax}
\renewcommand\footnoterule{%
  \kern-3\p@
  \hrule\@width.4\columnwidth
  \kern2.6\p@}
\newcommand\@makefntext[1]{%
    \parindent 1em%
    \noindent
    \hb@xt@1.8em{\hss\@makefnmark}#1}
\newcommand\contentsname{Contents}
\newcommand\listfigurename{List of Figures}
\newcommand\listtablename{List of Tables}
\newcommand\refname{References}
\newcommand\indexname{Index}
\newcommand\figurename{Figure}
\newcommand\tablename{Table}
\newcommand\partname{Part}
\newcommand\appendixname{Appendix}
\newcommand\abstractname{Abstract}

\setlength\columnsep{10\p@}
\setlength\columnseprule{0\p@}
\pagestyle{plain}
\pagenumbering{arabic}
\if@twoside
%%% CZY TAK CZY NIE?
  \raggedbottom
\else
  \raggedbottom
\fi
\if@twocolumn
  \twocolumn
  \sloppy
  \flushbottom
\else
  \onecolumn
\fi
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                  %%
%  Dodatkowe definicje                             %%
%                                                  %%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\def\newoddpage{\newpage\ifodd\c@page \else\hbox{} \thispagestyle{empty} \newpage\fi}

\let\newoddpagex\newoddpage

\def\newoddpagexxx{\let\newoddpage\newoddpagex }

\newif\ifJest \Jestfalse
\newif\ifJestleqno \Jestleqnofalse
\def\CzyJestCD{\ifx\CzyJestTMPA\CzyJestTMP \global\Jesttrue \fi}
\def\CzyJest#1{%\edef\ListaPlikow{\@filelist}%
\def\CzyJestTMP{#1}\@for\CzyJestTMPA:=\@filelist\do\CzyJestCD\relax}

\def\promotor#1{\gdef\@promotor{#1}}
\def\title#1{\gdef\@title{#1}}
\def\autor#1{\gdef\@autor{#1}}
\def\rodzPracy#1{\gdef\@rodzPracy{#1}}
\def\kierunek#1{\gdef\@kierunek{#1}}

\def\streszczenie#1{\gdef\@streszczenie{#1}}

\def\keys#1{\gdef\klu@cze{#1}}

\def\dziedzina#1#2{\gdef\@kdznr{#1}\gdef\@kdznazwa{#2}}

\newcount\nr@@klasy 
\nr@@klasy=0

\def\klasa#1#2{\global\advance\nr@@klasy1\relax
\expandafter\gdef\csname klasa@@a\the\nr@@klasy\endcsname{#1}
\global\advance\nr@@klasy1
\expandafter\gdef\csname klasa@@a\the\nr@@klasy\endcsname{#2}
}

\long\def\dedykacja#1{\gdef\@podziek{#1}
                 \let\podziek\ewpodziek }

\let\podziek\relax
\promotor{\WyjasnienieProm }
\def\rok#1{\gdef\@rok{#1}}
\rok{\the\year}
\let\xxdocument\document
\def\document{
\Jestfalse
\CzyJest{fleqn.clo}
\ifJest
     \ifJestleqno
        {\DodajNaPoczatek{\mathindent=45pt}}
\fi\fi
\xxdocument \relax
\let\xxprintindex\printindex
\def\printindex{\newoddpage
\addcontentsline{toc}{section}{Skorowidz}
\let\newoddpage\newoddpagexxx
\xxprintindex }
\poczatek }


\def\ZmianyOstateczne{}
\def\DodajNaPoczatek{\g@addto@macro\ZmianyOstateczne}

\def\nic{ }

\def\newlineSpis{\x@protect \\\protect \relax }
\def\newlineTekst{\x@protect \relax \protect \\}

\let\newlineB\newlineTresc
\let\newlineA\newlineSpis

\def\poczatek{\ZmianyOstateczne
\let\ZmianyOstateczne\@empty
\StronaTyt
 \hbox{}\thispagestyle{empty}

\newpage
\podziek
\global\count0=1


\gdef\kernsekcyjny{}
\gdef\kernsubsekcyjny{}
\gdef\kernsubsubsekcyjny{}
\global\let\savenumberline\numberline
\def\numberline##1{\hbox{##1. }}

\def\numberlineN##1{\hbox{##1. }}
\def\numberlineR##1{\hbox{Rozdzia\l \ ##1. }}

\spistresc

\global\let\numberline\savenumberline

}

\def\ewpodziek{%
  \thispagestyle{empty}%
  \hrule height0pt depth0pt
  \vfill\vfill\vfill
  \begingroup
    \rightskip=2cm
    \leftskip=4cm plus 1fill
    {\large\itshape
      \@podziek
    }
    \vskip2cm
    \vfill
  \endgroup
   \newpage
  \hbox{}\thispagestyle{empty}
  \newpage
}

\def\wstep{%
  \ustawKernyNorm
   \section*{Wst\k ep}%
    \addcontentsline{toc}{section}{Wst\k ep}%
    \markboth{WST\k EP\liniaA}{\liniaB WST\k EP}
     }

\def\wnioski{%
  \ustawKernyNorm
   \section*{Wnioski}%
    \addcontentsline{toc}{section}{Wnioski}%
    \markboth{WNIOSKI\liniaA}{\liniaB WNIOSKI}
     }
     
\def\rysunki{%
  \ustawKernyNorm
   \section*{Rysunki}%
    \addcontentsline{toc}{section}{Wnioski}%
    \markboth{RYSUNKI\liniaA}{\liniaB RYSUNKI}
     }
     
\def\dodatkowo#1{%
  \ustawKernyNorm
   \section*{#1}%
    \addcontentsline{toc}{section}{#1}%
    \markboth{\MakeUppercase{#1}\liniaA}{\liniaB \MakeUppercase{#1}}
     }

     
\let\spistresc\tableofcontents

%%%%%%%%%%%%%%%%%%%%%%%%%%%%55
% Strona tytulowa
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\newcommand{\fontnag}{\Large\scshape}
\newcommand{\fontrodzpracy}{\Large}
\newcommand{\fonttyt}{\Large}
\newcommand{\fontpromotor}{\Large}
\newcommand{\fontautor}{\Large}
\newcommand{\fontautoretyk}{\Large}
\newcommand{\fontpromotoretyk}{\Large}
\newcommand{\fontmiasto}{\large}

\def\StronaTyt{\thispagestyle{empty}
    \logo
    \GornaczescSytronyTyT
    \odstepGoraTytNap
    \wypisRodzajuPracy
    \odstepGoraTyt
    \wypisanieTyt
    \odsteptytAutorProm
    \wypisanieAutorPromotor
    \odstepAutorPromDol
    \dolnaczescStronyTyt
    \wykonajInneOperacje
}

\def\logo{
    \begin{figure}[th]
    \centering
    \includegraphics[width=75px, keepaspectratio=true]{./polsl}
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
   {\fontmiasto Gliwice, \miech }
     \end{center}\par\break
}

\def\odstepGoraTyt{\vskip-1pt\vskip0.5in\par\nointerlineskip}
\def\odstepGoraTytNap{\vfill\vfill}
\def\odsteptytAutorProm{\vfill\vfill\vfill\vfill\vfill\vfill}
\def\odstepAutorPromDol{\vskip0.5in\vfill}


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Wysokosc,
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\renewcommand\baselinestretch{1.3}
\def\marginesGorny{2.0cm}
\topmargin=-1in
\advance\topmargin \marginesGorny\relax
\@settopoint\topmargin
\textheight=23.5cm
%
% wyrownanie wysokosci dla bez akapitow
%
\@tempdimb \baselinestretch\baselineskip
\@tempdima\textheight
\divide\@tempdima\@tempdimb
\@tempcnta=\@tempdima
\setlength\textheight{\@tempcnta\@tempdimb}
\addtolength\textheight{\topskip}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  szeroksci
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% margines szcz\k atkowy
%
\marginparwidth=3mm
\@settopoint\marginparwidth

%
% Dane o marginesach i szyciu, reszata wyliczana przy zalozeniu 21cm szer.
%
\def\szerMarginesu{2cm}
\def\szerNaSzycie{2cm}

%
% wylicz szerokosc tekstu
%
\textwidth=21cm
\advance\textwidth by -\szerMarginesu\relax
\advance\textwidth by -\szerMarginesu\relax
\advance\textwidth by -\szerNaSzycie\relax

%
%  wpierw margines nieparzysty -1in == usunac hoffset
%                              potem na normalny margines bez szycia
%
\oddsidemargin=-1in
\advance\oddsidemargin\szerMarginesu


%
%  tu rowniez parzysty margines taki
%
\evensidemargin\oddsidemargin

%
%  nieparzysty zawsze ma miejsce na szycie
%
\advance\oddsidemargin by \szerNaSzycie

%
%  parzysty na szycie tylko w druku jesnostronnym:
%
\if@twoside \else
 \advance\evensidemargin by\szerNaSzycie
\fi

%
% wszelkie szerokosci wyrownac do pt.
%
\@settopoint\oddsidemargin
\@settopoint\evensidemargin
\@settopoint\textwidth
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  naglowki
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\def\liniaA{\vrule width-\textwidth depth3pt height-2.6pt
          \vrule width\textwidth depth3pt height-2.6pt\relax}
\def\liniaB{\vrule width\textwidth depth3pt height-2.6pt
          \vrule width-\textwidth depth3pt height-2.6pt\relax}


\pagestyle{myheadings}
\markboth{\MakeUppercase{Spis Tre\'sci}\liniaA}{\liniaB \MakeUppercase{Spis Tre\'sci}}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  r¢wnania
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\let\PrzedSection\relax
\let\PrzedSubSection\relax

\let\PrzedSectionx\relax
\let\PrzedSubSectionx\relax

\def\zerujLicznikRownan{\setcounter{equation}{0}}
\def\zerujLicznikRysunkow{\setcounter{figure}{0}}
\def\sectionWzory{\renewcommand \theequation {\thesection.\@arabic\c@equation}%
      \let\PrzedSection\zerujLicznikRownan
      \let\PrzedSubSection\relax          }
\def\subsectionWzory{\renewcommand \theequation {\thesubsection.\@arabic\c@equation}%
      \let\PrzedSection\zerujLicznikRownan
      \let\PrzedSubSection\zerujLicznikRownan
      }


\def\sectionRysunki{\renewcommand \thefigure {\thesection.\@arabic\c@figure}%
      \let\PrzedSectionx\zerujLicznikRysunkow
      \let\PrzedSubSectionx\relax          }

\def\subsectionRysunki{\renewcommand  \thefigure {\thesubsection.\@arabic\c@figure}%
      \let\PrzedSectionx\zerujLicznikRysunkow
      \let\PrzedSubSectionx\zerujLicznikRysunkow          }

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  sekcja do nag¢wka
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\def\ustawKernyNorm{
\def\kernsekcyjny{\kern-1em. }
\def\kernsubsekcyjny{\kern-1em. }
\def\kernsubsubsekcyjny{\kern-1em. }
}

\let\sectionXXX\section
\def\sectionXY[#1]#2{\def\NagText{\thesection. #1}%
\sectionXXX{\protect\kernsekcyjny #2}%
\markboth{\MakeUppercase\NagText\liniaA}{\liniaB\MakeUppercase\NagText}}
\def\section{\@ifnextchar*{\sectionXXX}{\@dblarg\sectionXY}}

\DodajNaPoczatek{\def\contentsname{Spis tre\'sci}}
\DodajNaPoczatek{\def\indexname{Skorowidz}}
\def\indexnameX{Skorowidz}
\def\indexnameY{\vbox to 12pt{\vss Skorowidz \vskip15pt\hrule height0pt}\vskip-8.3pt\relax}

\let\subsectionXXX\subsection
\def\subsectionYYY#1{\subsectionXXX{\protect\kernsubsekcyjny #1}}
\def\subsection{\@ifnextchar*{\subsectionXXX}{\subsectionYYY}}

\let\subsubsectionXXX\subsubsection
\def\subsubsectionYYY#1{\subsubsectionXXX{\protect\kernsubsubsekcyjny #1}}
\def\subsubsection{\@ifnextchar*{\subsubsectionXXX}{\subsubsectionYYY}}

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% kropki w twierdzeniach
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\def\@xthm#1#2{\@begintheorem{#2}{\csname the#1\endcsname.}\ignorespaces}
\def\@ythm#1#2[#3]{\@opargbegintheorem{#2}{\csname the#1\endcsname.}{#3}\ignorespaces}

\def\NumeryNaPoczatku{
\def\@xthm##1##2{\@begintheorem{\csname the##1\endcsname.}{##2}\ignorespaces}
\def\@ythm##1##2[##3]{\@opargbegintheorem{\csname the##1\endcsname.}{##2}{##3}\ignorespaces}
}
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%
%% DODATKI
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\newcounter{numeracjadod} \setcounter{numeracjadod}{0}
\def\dodatekNr{\ewspac\spos{numeracjadod}}
\def\usun#1{}

\def\rzymskaNumeracjaDodatkow{\let\spos\Roman \def\ewspac{ }}
\def\literowaNumeracjaDodatkow{\let\spos\Alph \def\ewspac{ }}
\def\bezNumeracjiDodatkow{\let\spos\usun \def\ewspac{}}

\bezNumeracjiDodatkow

\def\dodatek{\addtocounter{numeracjadod}{1}%
\@ifnextchar*{\dodatekX}{\@dblarg\dodatekY}}
\def\dodatekX*{\@dblarg\dodatekXY}

\def\dodatekY[#1]#2{\def\xtmp{#1}%
\section*{Dodatek\dodatekNr}\vskip-30pt
\subsection*{#2}\vskip30pt
\ifx\xtmp\@empty
\def\NagText{Dodatek\dodatekNr}%
\else
\def\NagText{Dodatek\dodatekNr: #1}%
\fi
\markboth{\MakeUppercase\NagText\liniaA}{\liniaB\MakeUppercase\NagText}%
\def\xtmp{#2}%
\ifx\xtmp\@empty
\addcontentsline{toc}{section}{Dodatek\dodatekNr}%
\else
\addcontentsline{toc}{section}{Dodatek\dodatekNr: #2}%
\fi
}

\def\dodatekXY[#1]#2{\def\xtmp{#1}%
\section*{Dodatek\dodatekNr}\vskip-30pt
\subsection*{#2}\vskip30pt
\ifx\xtmp\@empty
\def\NagText{Dodatek\dodatekNr}%
\else
\def\NagText{Dodatek \dodatekNr: #1}%
\fi
\markboth{\MakeUppercase\NagText\liniaA}{\liniaB\MakeUppercase\NagText}%
}

\author{}
\title{}

\rodzajKodow

\def\@seccntformatSPEC#1{
\begingroup
\lower-2cm\hbox to 0pt{Rozdzia\l\
\csname the#1\endcsname\hss }\endgroup}
\def\znikajKropko{}%
\def\rozdzialy{%
   \let\seczwykform\@seccntformat
   \let\sectionXYZ\section
   \def\section{\let\kernsekcyjny\znikajKropko \let\@seccntformat\@seccntformatSPEC\sectionXYZ }
   \let\subsectionXYZ\subsection
   \def\subsection{\let\@seccntformat\seczwykform\subsectionXYZ }
}

\def\rozdzialyx{\rozdzialy
\renewcommand*\l@section[2]{%
  \ifnum \c@tocdepth >\z@
    \addpenalty\@secpenalty
    \addvspace{1.0em \@plus\p@}%
    \setlength\@tempdima{3em}%
    \let\numberline\numberlineR
    \begingroup
      \parindent \z@ \rightskip \@pnumwidth
      \parfillskip -\@pnumwidth
      \leavevmode \bfseries
      \advance\leftskip\@tempdima
      \hskip -\leftskip
      ##1\nobreak\hfil \nobreak\hb@xt@\@pnumwidth{\hss ##2}\par
    \endgroup
  \fi}
\renewcommand*\l@subsection{\let\numberline\numberlineN \@dottedtocline{2}{1.5em}{2.8em}}			
}

\def\rzymskieRozdzialy{
\renewcommand{\thesection}{\Roman{section}%
 }
\renewcommand{\thesubsection}{\Roman{section}.\arabic{subsection}%
}
\renewcommand{\thesubsubsection}{\Roman{section}.%
       \arabic{subsection}.\arabic{subsubsection}%
}
\renewcommand*\l@section[2]{%
  \ifnum \c@tocdepth >\z@
    \addpenalty\@secpenalty
    \addvspace{1.0em \@plus\p@}%
    \setlength\@tempdima{3em}%
    \begingroup
      \parindent \z@ \rightskip \@pnumwidth
      \parfillskip -\@pnumwidth
      \leavevmode \bfseries
      \advance\leftskip\@tempdima
      \hskip -\leftskip
      ##1\nobreak\hfil \nobreak\hb@xt@\@pnumwidth{\hss ##2}\par
    \endgroup
  \fi}
\renewcommand*\l@subsection{\@dottedtocline{2}{1.5em}{3.8em}}
\renewcommand*\l@subsubsection{\@dottedtocline{3}{3.8em}{5em}}
}

\def\wykonajInneOperacje{}
\def\drukJednostronny{
\advance\evensidemargin by\szerNaSzycie
\def\wykonajInneOperacje{%
    \def\@evenhead{{\slshape\rightmark}\hfil\thepage}%
    \def\@oddhead{{\slshape\rightmark}\hfil\thepage}%
}}

%polskie składanie - sieroty wdowy itp
\widowpenalty=10000 %nie pozostawia wdów na ko«cu strony
\clubpenalty=10000 %nie pozostawia sierot
\brokenpenalty=10000 %nie dzieli stron je»eli podziaa wyrazu

% dla kompatybilnosci:
\let\xle\le \let\xge\ge

\endinput
