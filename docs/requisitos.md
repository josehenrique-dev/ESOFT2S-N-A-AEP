# Requisitos do Sistema - PSE em Ação

**Projeto:** Sistema de Planejamento e Acompanhamento de Ações de Saúde na Escola
**Curso:** Engenharia de Software / Análise e Desenvolvimento de Sistemas - ESOFT2S / ADSIS2S
**Instituição:** UniCesumar - 2º Semestre 2026

---

## 1. Requisitos Funcionais

| ID   | Nome                        | Descrição                                                                                                                                                                      | Prioridade |
|------|-----------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------|
| RF01 | Cadastrar ação do PSE       | O sistema deve permitir o cadastro de uma nova ação informando: código (inteiro único), escola, tema, data prevista (DD/MM/AAAA), público-alvo, responsável, quantidade prevista de participantes e situação inicial (planejada). | Alta       |
| RF02 | Listar ações cadastradas    | O sistema deve exibir todas as ações cadastradas em formato de lista organizada, apresentando todos os campos de cada registro de forma legível no terminal.                     | Alta       |
| RF03 | Pesquisar ação              | O sistema deve permitir a localização de ações por três critérios: (a) código exato, (b) nome da escola (busca parcial, sem distinção de maiúsculas/minúsculas) ou (c) tema (busca parcial). | Alta       |
| RF04 | Atualizar situação da ação  | O sistema deve permitir alterar a situação de uma ação (planejada → realizada ou cancelada). Quando marcada como realizada, o sistema deve solicitar a quantidade efetiva de participantes. | Alta       |
| RF05 | Gerar resumo geral          | O sistema deve apresentar um painel consolidado com: total de ações por situação (planejada, realizada, cancelada), soma de participantes previstos, soma de participantes efetivos e percentual de participação. | Alta       |
| RF06 | Validar entradas            | O sistema deve rejeitar: códigos duplicados, quantidades negativas ou zero, campos obrigatórios em branco e opções inexistentes no menu, exibindo mensagem de erro em cada caso. | Alta       |
| RF07 | Menu interativo com loop    | O sistema deve exibir um menu principal com todas as opções disponíveis e permanecer ativo até que o usuário escolha a opção de encerramento.                                   | Alta       |
| RF08 | Submenu de pesquisa         | O sistema deve oferecer um submenu que permita ao usuário escolher o critério de pesquisa (código, escola ou tema) antes de realizar a busca.                                   | Média      |

---

## 2. Requisitos Não Funcionais

| ID    | Categoria       | Descrição                                                                                                                                           |
|-------|-----------------|-----------------------------------------------------------------------------------------------------------------------------------------------------|
| RNF01 | Usabilidade     | O sistema deve exibir mensagens claras de confirmação após cada operação bem-sucedida e mensagens de erro descritivas em caso de entrada inválida.  |
| RNF02 | Desempenho      | O sistema deve responder a qualquer operação em tempo imediato, sem atrasos perceptíveis, para até 50 ações cadastradas.                            |
| RNF03 | Manutenibilidade| O código-fonte deve ser organizado em funções com responsabilidades únicas e bem definidas, com comentários apenas onde a lógica não for autoevidente. |
| RNF04 | Privacidade     | O sistema não deve armazenar, solicitar ou exibir dados clínicos, diagnósticos, prontuários ou qualquer informação pessoal de estudantes individuais. |
| RNF05 | Portabilidade   | O sistema deve compilar e executar em ambientes Linux, macOS e Windows (via MinGW/WSL) utilizando o compilador GCC com o padrão C99 ou superior.    |

---

## 3. Restrições do Sistema

- **Capacidade:** máximo de 50 ações armazenadas simultaneamente em memória.
- **Persistência:** armazenamento apenas em memória durante a execução (sem arquivos ou banco de dados).
- **Interface:** exclusivamente em terminal/console (sem interface gráfica ou web).
- **Linguagem:** implementado integralmente em linguagem C (padrão C99).
- **Bibliotecas:** apenas bibliotecas padrão da linguagem C (`stdio.h`, `stdlib.h`, `string.h`).
- **Dados:** utilização exclusiva de dados fictícios; nenhum dado sensível individual de estudantes.
- **Escopo médico:** o sistema não realiza triagem, diagnóstico, prescrição ou recomendação clínica.

---

## 4. Regras de Negócio

| ID   | Regra                                                                                                                  |
|------|------------------------------------------------------------------------------------------------------------------------|
| RN01 | O código de cada ação deve ser um número inteiro positivo e único no sistema.                                          |
| RN02 | A situação inicial de toda ação cadastrada é automaticamente definida como **Planejada**.                               |
| RN03 | A quantidade efetiva de participantes só pode ser registrada quando a situação for atualizada para **Realizada**.       |
| RN04 | Uma ação **Cancelada** não pode ter quantidade efetiva de participantes registrada.                                     |
| RN05 | O percentual de participação é calculado como: `(total efetivo / total previsto) × 100`, somente para ações realizadas.|
| RN06 | A pesquisa por escola e por tema deve ser case-insensitive (sem distinção entre maiúsculas e minúsculas).              |

---

## 5. Atores do Sistema

| Cargo         | Nome                           |
|---------------|--------------------------------|
| Product Owner | José Henrique Olinto Pereira   |
| Scrum Master  | Caio Vinicius Patrono Oliveira |
| Desenvolvedor | Pedro Henrique Camilo Bett     |

---

## 6. Escopo Delimitado

**Dentro do escopo:**
- Cadastro, listagem, pesquisa, atualização e resumo de ações coletivas do PSE.
- Validação de entradas no terminal.
- Dados sobre a ação (escola, tema, responsável, datas, quantidades, situação).

**Fora do escopo:**
- Autenticação e controle de acesso por usuário.
- Persistência em banco de dados ou arquivo.
- Interface gráfica ou aplicação web.
- Qualquer dado clínico ou individual de estudantes.
- Integração com outros sistemas.
