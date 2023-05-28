<img src="LANDrop/icons/banner.png" width="300">

> Copier des fichiers depuis n'importe quel périphérique vers une borne de stockage.

LANDrop est un logiciel cross-platform qui permet de copier très rapidement et très simplement des fichiers entre différents matériels d'un réseau local.
Vous pouvez télécharger les clients pour chaque plateforme ici : https://landrop.app/#downloads.

BorneLANDrop est une modification de la version Linux du logiciel. Il est detiné à réliser une borne de stockage, à base de RaspBerry-PI permettant de récupérer et de stocker sur une clef USB les fichiers médias (photos, vidéo) réalisé par les élèves avec leur téléphone.

Vous pouvez télécharger une version complié pour PI OS (raspbian) à cette adresse [du-man.net](https://www.du-man.net/#downloads).

## Modification par rapport à la version d'origine

- Cette version est compatible avec tous les clients : iOS, Android, macOS, Windows, Linux.
- Elle apparait sous forme d'application et pas d'icone.
- Les ficihiers s'enregistrent sans autorisation préalable.
- Les fichiers ne sont enregistrés que sur des supports de stockage ammovibles.
- L'ajout et le retrait des supports de stockage sont détéctés automatiquement.
- La pluspart des réglages ont été supprimés pour rendre l'utilisation aussi simple que possible. 

## Building

Si l'image compilé ne focntionne pas sur votre machine, vous pouvez la compiler vous même avec les instructions suivantes.

To build LANDrop:

1. Download and install the dependencies: [Qt](https://www.qt.io/download-qt-installer) and [libsodium](https://libsodium.gitbook.io/doc/#downloading-libsodium)  
    If you are using a Debian-based distro, such as Ubuntu, you can install libsodium via
    ```
    sudo apt install libsodium-dev
    ```
2. Clone this repository
    ```
    git clone https://github.com/du-man/BorneLANDrop
    ```
3. Run the following commands
    ```
    mkdir -p BorneLANDrop/build
    cd BorneLANDrop/build
    qmake ../LANDrop
    make -j$(nproc)
    sudo make install
    ```
4. You can now run LANDrop via
    ```
    landrop
    ```
