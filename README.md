# MinOS - Bare Metal OS

<!-- English -->
## About
A mini bare-metal operating system built from scratch. Features a bootloader written in NASM, a C kernel, VGA text-mode printing, and an Interrupt Descriptor Table (IDT) for keyboard handling.

### Prerequisites
* QEMU (x86 emulator)
* C compiler (GCC)
* NASM assembler
* Make

### Build & Run
```bash
make run

# MinOS - Système d'exploitation Bare Metal

## À propos
Un mini système d'exploitation *bare-metal* conçu de zéro. Il comprend un chargeur d'amorçage (*bootloader*) écrit en NASM, un noyau en C, l'affichage en mode texte VGA et une table de description des interruptions (IDT) pour la gestion du clavier.

### Prérequis
* QEMU (émulateur x86)
* Compilateur C (GCC)
* Assembleur NASM
* Make

### Compiler & exécuter
```bash
make run