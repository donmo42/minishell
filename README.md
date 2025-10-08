# minishell
![ (minishell)](./minishelle.png)
🐚 Minishell : L'interpréteur de Commandes de 42

🚀 Introduction

Ce projet, Minishell, est une étape fondamentale dans le cursus 42. Son objectif est de créer notre propre interpréteur de commandes (shell), fonctionnellement similaire à Bash (ou d'autres shells Unix courants).

En recréant les mécanismes internes d'un shell, nous visons à maîtriser l'interaction entre un programme utilisateur et le système d'exploitation, ainsi qu'à renforcer notre compréhension des concepts clés de la programmation système.

🖼️ Structure du Projet

Voici un aperçu de la structure de l'interpréteur et du flux des données.

**

✨ Fonctionnalités Implémentées

Notre minishell supporte une grande partie des fonctionnalités essentielles d'un shell moderne, notamment :

1. Gestion des Commandes et de l'Environnement

    Gestion des variables d'environnement: Manipulation des variables d'environnement (PATH, HOME, etc.) et implémentation des fonctions primitives (built-ins) comme cd, echo, pwd, export, unset, et exit.

    Recherche de commandes: Identification et résolution des chemins des exécutables en utilisant la variable $PATH.

    Exit status ($?): Correctement gérer et retourner le statut de sortie de la dernière commande exécutée.

2. Le cœur du Shell : Processus et I/O

    Gestion des processus : Utilisation des appels système de bas niveau (fork(), execve(), waitpid()) pour exécuter des commandes externes en tant que processus enfants.

    Redirection des Entrées/Sorties (I/O) :

        Redirection de sortie simple (>): Écrire la sortie dans un fichier (création ou écrasement).

        Redirection d'ajout (>>): Écrire la sortie en ajoutant à la fin d'un fichier.

        Redirection d'entrée (<): Lire l'entrée depuis un fichier.

        Here Document (<<): Lire des lignes d'entrée directement depuis le terminal jusqu'à ce qu'un délimiteur spécifique soit rencontré.

    Gestion des Pipes (|) : Enchaîner des commandes pour que la sortie de la première devienne l'entrée de la suivante (ls | grep). Cela nécessite la manipulation des descripteurs de fichiers et des processus.

3. Parsing et Interprétation

    Tokenisation : Découpage de la ligne de commande brute en éléments logiques (tokens : commandes, arguments, opérateurs, redirections).

    Gestion des Quotes : Interprétation correcte des guillemets doubles (") et guillemets simples (') pour prévenir l'interprétation ou l'expansion des variables.

    Expansion des Variables : Remplacement des variables d'environnement ($USER, $HOME, etc.) par leur valeur avant l'exécution.

4. Robustesse et Gestion des Signaux

    Gestion des Signaux : Capturer et gérer les signaux du système (avec sigaction()):

        Ctrl+C (SIGINT) : Afficher un nouveau prompt ou terminer la commande en cours.

        Ctrl+\ (SIGQUIT) : Ignoré en mode interactif.

        Ctrl+D (EOF) : Fermeture du shell (exit).
    C'est un excellent exercice ! Voici un README.md complet et bien structuré, prêt à être copié dans votre projet minishell.

J'ai inclus une section pour l'image, le but, les fonctionnalités clés, et les compétences acquises.

🐚 Minishell : L'interpréteur de Commandes de 42

🚀 Introduction

Ce projet, Minishell, est une étape fondamentale dans le cursus 42. Son objectif est de créer notre propre interpréteur de commandes (shell), fonctionnellement similaire à Bash (ou d'autres shells Unix courants).

En recréant les mécanismes internes d'un shell, nous visons à maîtriser l'interaction entre un programme utilisateur et le système d'exploitation, ainsi qu'à renforcer notre compréhension des concepts clés de la programmation système.

🖼️ Structure du Projet

Voici un aperçu de la structure de l'interpréteur et du flux des données.

**

✨ Fonctionnalités Implémentées

Notre minishell supporte une grande partie des fonctionnalités essentielles d'un shell moderne, notamment :

1. Gestion des Commandes et de l'Environnement

    Gestion des variables d'environnement: Manipulation des variables d'environnement (PATH, HOME, etc.) et implémentation des fonctions primitives (built-ins) comme cd, echo, pwd, export, unset, et exit.

    Recherche de commandes: Identification et résolution des chemins des exécutables en utilisant la variable $PATH.

    Exit status ($?): Correctement gérer et retourner le statut de sortie de la dernière commande exécutée.

2. Le cœur du Shell : Processus et I/O

    Gestion des processus : Utilisation des appels système de bas niveau (fork(), execve(), waitpid()) pour exécuter des commandes externes en tant que processus enfants.

    Redirection des Entrées/Sorties (I/O) :

        Redirection de sortie simple (>): Écrire la sortie dans un fichier (création ou écrasement).

        Redirection d'ajout (>>): Écrire la sortie en ajoutant à la fin d'un fichier.

        Redirection d'entrée (<): Lire l'entrée depuis un fichier.

        Here Document (<<): Lire des lignes d'entrée directement depuis le terminal jusqu'à ce qu'un délimiteur spécifique soit rencontré.

    Gestion des Pipes (|) : Enchaîner des commandes pour que la sortie de la première devienne l'entrée de la suivante (ls | grep). Cela nécessite la manipulation des descripteurs de fichiers et des processus.

3. Parsing et Interprétation

    Tokenisation : Découpage de la ligne de commande brute en éléments logiques (tokens : commandes, arguments, opérateurs, redirections).

    Gestion des Quotes : Interprétation correcte des guillemets doubles (") et guillemets simples (') pour prévenir l'interprétation ou l'expansion des variables.

    Expansion des Variables : Remplacement des variables d'environnement ($USER, $HOME, etc.) par leur valeur avant l'exécution.

4. Robustesse et Gestion des Signaux

    Gestion des Signaux : Capturer et gérer les signaux du système (avec sigaction()):

        Ctrl+C (SIGINT) : Afficher un nouveau prompt ou terminer la commande en cours.

        Ctrl+\ (SIGQUIT) : Ignoré en mode interactif.

        Ctrl+D (EOF) : Fermeture du shell (exit).

🛠️ Compétences et Concepts Maîtrisés

Ce projet a permis de développer une compréhension profonde des concepts suivants :
Catégorie	Compétences Clés
Programmation Système	<ul><li>Utilisation et manipulation des appels système de processus (fork, execve, waitpid).</li><li>Maîtrise de la gestion des descripteurs de fichiers et des I/O (open, read, write, close, dup2).</li><li>Création et gestion des pipes (pipe()).</li></ul>
Gestion de la Mémoire	<ul><li>Gestion rigoureuse des allocations (pas de fuites mémoire).</li><li>Manipulation sécurisée des chaînes de caractères et des tableaux de chaînes.</li></ul>
Structure de Données	<ul><li>Conception de structures de données pour représenter la ligne de commande (ex: liste chaînée de tokens ou de commandes).</li></ul>
Code et Robustesse	<ul><li>Modularité et lisibilité du code (norme 42).</li><li>Gestion des erreurs et robustesse face aux entrées utilisateur inattendues.</li></ul>
⚙️ Installation et Utilisation

Prérequis

    make

    cc (compilateur C)

    La librairie readline (souvent disponible via brew install readline sur macOS ou sudo apt-get install libreadline-dev sur Linux).
    git clone https://github.com/donmo42/minishell
cd minishell - 
make -
./minishell