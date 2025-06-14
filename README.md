# Sistemas Embarcados - Projetos Práticos

Este repositório contém os projetos desenvolvidos durante a disciplina de **Sistemas Embarcados** do curso de Engenharia Elétrica, cursada no período 2025.1 na Universidade Federal de Campina Grande (UFCG).

## 🎯 Objetivo da Disciplina

A disciplina tem como foco a aplicação prática de conceitos de sistemas embarcados por meio da modernização (retrofit) da placa **MCLAB2 V5.0**, substituindo seu microcontrolador original, o **PIC16F877A**, por microcontroladores modernos de 8 e 32 bits. Ao final, é realizada uma aplicação real com a placa atualizada.

A disciplina é dividida em três etapas principais:

1. **Retrofit 8 bits**  
   Substituição do microcontrolador da placa MCLAB2 V5.0 por um **ATmega328P**, com reconfiguração dos periféricos.

2. **Retrofit 32 bits**  
   Nova substituição do microcontrolador, agora por um **STM32F401RE**, com reestruturação completa do sistema e reprogramação da placa.

3. **Aplicação Final**  
   Desenvolvimento de uma aplicação real utilizando a placa MCLAB2 V5.0 atualizada, explorando as capacidades do microcontrolador de 32 bits.

## 🛠️ Tecnologias e Ferramentas

- **ATmega328P (8-bit AVR)**
- **STM32F401RE (ARM Cortex-M4, 32-bit)**
- **PIC16F877A (original da placa)**
- **Placa MCLAB2 V5.0**
- **Microchip Studio**
- **Linguagem de programação C**

## 📁 Estrutura dos Projetos

```bash
/
├── Retrofit_8bits_ATmega328p/
│   ├── README.md
│   └── arquivos-fonte/
├── Retrofit-32bits-STM32f401RE/
│   ├── README.md
│   └── arquivos-fonte/
└── Aplicacao_Final/
    ├── README.md
    └── arquivos-fonte/

