\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{report}
\ProcessOptions

\LoadClass[12pt, a4paper, final]{extreport}

\RequirePackage{cmap}				% Поиск в PDF
\RequirePackage{paratype}			% Кириллица
\RequirePackage[unicode, hidelinks]{hyperref}
\RequirePackage{mathtext}			% Русские буквы в формулах
\RequirePackage[T2A, OT1]{fontenc}		% Кодировка
\RequirePackage[utf8]{inputenc}		% Кодировка исодного текста

\RequirePackage[english, russian]{babel}	% Локализация и переносы
\RequirePackage{indentfirst}			% Отступ в начале параграфа


% Разметка
\RequirePackage[top=2cm, bottom = 3cm, footskip=1cm, left=2.5cm, right=2cm]{geometry}
\RequirePackage[onehalfspacing]{setspace}
\setlength{\parindent}{1.25cm}
\setlength{\parskip}{1ex plus .5ex minus .3ex}
\setlength{\skip\footins}{.6in plus .3in minus .2in}

\pretolerance=9999
\tolerance=9999
\hyphenpenalty=9999
\emergencystretch=2cm

\RequirePackage{enumitem}
	\setlist{nolistsep, itemsep=\parskip, leftmargin=!}
\RequirePackage[bottom]{footmisc}
\RequirePackage{array}
	\renewcommand{\arraystretch}{1.5}		% Таблицы красивее





% Графика
\RequirePackage{graphicx}	% Для вставки рисунков
\graphicspath{{images/}}		% Папки с картинками
\setlength\fboxsep{3pt}		% Отступ рамки \fbox{} от рисунка
\setlength\fboxrule{1pt}		% Толщина линий рамки \fbox{}
\RequirePackage{color}
\RequirePackage{float}
\RequirePackage{wrapfig}
\RequirePackage{caption}
\RequirePackage{subcaption}

\renewcommand\thesubfigure{\asbuk{subfigure}}

% Таблицы
\RequirePackage{array, tabularx, tabulary, booktabs}	% Дополнительная работа с таблицами
\RequirePackage{longtable}					% Длинные таблицы
\RequirePackage{multicol}
\RequirePackage{multirow}					% Слияние строк в таблице
\newcommand{\RomanNumeralCaps}[1]
	{\MakeUppercase{\romannumeral #1}}

\RequirePackage{pdflscape}
\RequirePackage{tikz, pgfplots, pgfplotstable}
	\pgfplotsset{compat = 1.18}
\RequirePackage{lscape}

\RequirePackage{circuitikz}				% Electrical networks

\RequirePackage[justification=centering]{caption}









% AMS-LaTeX & math
\RequirePackage{amsfonts}
\RequirePackage{amsmath}
\RequirePackage{amssymb}
\RequirePackage{amsthm}
\RequirePackage{mathtools}
\RequirePackage{cancel}
\RequirePackage{mathrsfs}
\RequirePackage{icomma}			% Умная запятая

% Показывать номера только у тех формул, на которые есть \eqref{} в тексте
\mathtoolsset{showonlyrefs=true}

%% Перенос знаков в формулах (по Львовскому)
\newcommand*{\hm}[1]{#1\nobreak\discretionary{}
	{\hbox{$\mathsurround=0pt #1$}}{}}





\AtBeginDocument{\def\contentsname{Содержание}}





\input{commands.cls}