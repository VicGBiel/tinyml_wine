# TinyML - Classificação de Vinho (Raspberry Pi Pico)

Este projeto implementa um modelo de Machine Learning (TinyML) para rodar no **Raspberry Pi Pico (RP2040)**. O objetivo é realizar a inferência de qualidade de vinhos utilizando o TensorFlow Lite for Microcontrollers.

## ⚙️ Instalação e Configuração

Siga estes passos exatos para preparar o projeto:

### 1. Clonar o Projeto
Abra o terminal (Git Bash ou PowerShell) e rode:

```bash
git clone <URL_DO_SEU_REPOSITORIO>
cd tinyml_wine
```

### 2. Instalar a Biblioteca TFLite
Este projeto depende da biblioteca `pico-tflmicro`. Você precisa cloná-la manualmente dentro da pasta `lib` para que o CMake a encontre.

Execute os comandos abaixo na **raiz do projeto**:

```bash
# 1. Cria a pasta lib (se ela ainda não existir)
mkdir lib

# 2. Entra na pasta
cd lib

# 3. Clona o repositório oficial do TensorFlow Lite para Pico
git clone https://github.com/raspberrypi/pico-tflmicro.git

# 4. Volta para a raiz do projeto
cd ..
```

> **Verificação:** A estrutura final de pastas deve ficar assim:
> `tinyml_wine/lib/pico-tflmicro/`

---

## 🚀 Como Rodar

1.  Conecte o Raspberry Pi Pico ao USB segurando o botão branco **BOOTSEL**.
2.  O computador irá reconhecer uma unidade de disco chamada `RPI-RP2`.
3.  Vá até a pasta `build` do projeto (dentro de tinyml_wine).
4.  Arraste o arquivo **`.uf2`** gerado para dentro da unidade `RPI-RP2`.
5.  O Pico irá reiniciar automaticamente e rodar a inferência.

---

## 🔍 Monitoramento

Para ver os resultados da classificação:
1.  Use um monitor serial (Serial Monitor do VS Code, Putty ou Arduino IDE).
2.  Configure para a porta COM do Pico.
3.  **Baud Rate:** 115200.

---