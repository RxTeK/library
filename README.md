# 📚 Library --- C++ Utilities for Unreal Engine

Library est une collection de fonctions C++ faites pour **simplifier et
accélérer l'écriture de code dans Unreal Engine**.\
Elle permet d'éviter les lignes longues et répétitives, en offrant des
raccourcis pratiques pour le debug et d'autres tâches fréquentes.

La librairie sera mise à jour régulièrement en fonction des besoins de
nos projets.

------------------------------------------------------------------------

## ✨ Exemple d'utilisation

Sans la librairie :

``` cpp
GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Green,);
```

Avec la librairie :

``` cpp
MaLib::Print("Hello World", 2, FColor::Green);
```

Plus simple. Plus propre. Plus rapide.

------------------------------------------------------------------------

## 🚀 Installation

1.  Télécharge le fichier `.h` depuis ce dépôt\
2.  Place-le dans le dossier **Public/** de ton module Unreal Engine\
3.  Ajoute l'include :

``` cpp
#include "Library.h"
```

Et c'est tout.

------------------------------------------------------------------------

## 🔧 Compatibilité

-   ✔️ Unreal Engine 5\
-   ❓ Unreal Engine 4 (probablement compatible mais non testé)

------------------------------------------------------------------------

## 📌 Fonctionnalités actuelles

-   Fonctions de debug simplifiées\
-   Mises à jour fréquentes selon les besoins

------------------------------------------------------------------------

## 🛠️ Contribution

Tu peux proposer des améliorations ou ajouter tes propres fonctions via
une issue ou une pull request.
