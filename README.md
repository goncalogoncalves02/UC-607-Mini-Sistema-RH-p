# Mini Sistema RH 🧑‍💼

## 🚀 Visão Geral
- Aplicação de consola para gerir colaboradores, ausências e calendários.
- Guardar dados cifrados num ficheiro CSV simples, ideal para aprendizagem.
- Baseada em C++ moderno, organizada por camadas (controllers, models, views).

## ✨ Funcionalidades Principais
- `Adicionar colaborador`: regista novos elementos da equipa evitando duplicados.
- `Listar colaboradores`: apresenta todos os nomes carregados do ficheiro.
- `Marcar/Desmarcar ausência`: regista férias ou faltas validando datas úteis.
- `Visualizar calendário`: mostra calendário mensal com marca para férias (F), faltas (X) e fins de semana (W).
- `Persistência segura`: encripta o nome dos colaboradores antes de gravar.

## 🧱 Arquitetura do Projeto
- `main.cpp`: ciclo principal de menu e interação com o utilizador.
- `controllers/gestor_rh.*`: coordena operações de negócio (CRUD e validações).
- `models/colaborador.*`: representa colaborador e ausências.
- `models/persistencia.*`: leitura/escrita do CSV com cifragem César.
- `models/util_data.*`: funções de datas (dias do mês, dia da semana, validação).
- `views/calendario.*`: renderiza calendário mensal na consola.

## 📦 Dependências
- Compilador C++11 ou superior (testado com `g++`).
- Sistema operativo com terminal e biblioteca padrão (iostream, fstream, etc.).

## 🛠️ Compilação
Compilar tudo de uma vez diretamente no terminal:

```bash
g++ main.cpp controllers/gestor_rh.cpp views/calendario.cpp models/colaborador.cpp models/persistencia.cpp models/cifra.cpp models/util_data.cpp -o mini_rh.exe
```

## ▶️ Execução
- No Windows: `.\mini_rh.exe`
- No Linux/macOS: `./mini_rh.exe`
- Ao iniciar, o programa tenta carregar `colaboradores.csv`. Se não existir, será criado ao gravar.

## 🗂️ Estrutura de Pastas
```text
.
├── controllers/        # Regras de negócio e menus
├── models/             # Entidades, persistência e utilitários
├── views/              # Saída formatada (calendário)
├── colaboradores.csv   # Base de dados simples (criado ao gravar)
└── mini_rh.exe         # Executável gerado após compilação
```

## 💾 Persistência e Cifragem
- Os nomes são guardados cifrados com uma versão simples da cifra de César.
- Cada ausência fica guardada como `AAAA-MM-DD,Símbolo`, onde `Símbolo` é `F` (férias) ou `X` (falta).
- Datas inválidas são ignoradas na leitura para evitar corrupção dos dados.

## 🗓️ Dicas de Utilização
- Registe primeiro os colaboradores antes de marcar ausências.
- Use apenas dias úteis para férias/faltas; o programa bloqueia fins de semana.
- O calendário realça fins de semana com `W` para facilitar leitura rápida.

## 🎯 Próximos Passos Sugeridos
1. Automatizar testes unitários para funções de datas e cifragem.
2. Adicionar suporte a diferentes tipos de ausência (ex. teletrabalho, baixa).
3. Exportar calendários em formato PDF/HTML para partilha externa.
