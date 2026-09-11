# PSE em Ação

Sistema de Planejamento e Acompanhamento de Ações de Saúde na Escola - aplicação em terminal desenvolvida em linguagem C.

**Instituição:** UniCesumar - Universidade Cesumar
**Curso:** Engenharia de Software / Análise e Desenvolvimento de Sistemas
**Série:** ESOFT2S / ADSIS2S - 2º Semestre 2026
**Disciplinas:** Algoritmos e Lógica de Programação · Engenharia de Software · Produção Textual

---

## Integrantes

| Nome                           | RA         |
|--------------------------------|------------|
| Caio Vinicius Patrono Oliveira | 26001378-2 |
| José Henrique Olinto Pereira   | 26010549-2 |
| Pedro Henrique Camilo Bett     | 26001933-2 |

---

## Sobre o Projeto

O **PSE em Ação** é uma aplicação de terminal desenvolvida como Atividade de Extensão e Pesquisa (AEP) para apoiar o planejamento e o acompanhamento de ações coletivas do [Programa Saúde na Escola (PSE)](https://www.gov.br/saude/pt-br/composicao/saps/pse), instituído pelo Decreto nº 6.286/2007.

O sistema permite que equipes intersetoriais de saúde e educação cadastrem, consultem e acompanhem ações como campanhas de vacinação, atividades de saúde mental, alimentação saudável e outras iniciativas do PSE.

---

## Funcionalidades

| # | Funcionalidade |
|---|---------------|
| 1 | Cadastrar ação (código, escola, tema, data, público-alvo, responsável, quantidade prevista) |
| 2 | Listar todas as ações cadastradas |
| 3 | Pesquisar ações por código, escola ou tema |
| 4 | Atualizar situação (planejada / realizada / cancelada) e registrar participantes efetivos |
| 5 | Gerar resumo geral com totais e percentual de participação |
| 6 | Validação completa de entradas |

---

## Documentação

| Documento                                            | Descrição                                                                                    |
|------------------------------------------------------|----------------------------------------------------------------------------------------------|
| [`Requisitos`](./requisitos.md)                      | 8 requisitos funcionais, 5 não funcionais, regras de negócio, atores e escopo                |
| [`Fluxograma Geral`](./fluxograma-geral.png)         | Fluxogramas do menu, cadastro, pesquisa, atualização e resumo                   |
| [`Fluxograma Detalhado`](./fluxograma-detalhado.png) | Fluxogramas de cadastro de uma ação  |
| [`Documento Academico`](./documento_academico.pdf)   | Contextualização do PSE, problema, objetivos, justificativa, planejamento de sprints e referências |

---

## Restrições do Sistema

- Máximo de **50 ações** armazenadas em memória por execução
- Armazenamento apenas em memória (sem banco de dados ou arquivos)
- Nenhum dado clínico, diagnóstico ou informação individual de estudantes
- Apenas bibliotecas padrão da linguagem C (`stdio.h`, `stdlib.h`, `string.h`, `ctype.h`)

---

## Referências

BRASIL. Decreto nº 6.286, de 5 de dezembro de 2007. *Diário Oficial da União*, Brasília, 6 dez. 2007.

BRASIL. Ministério da Saúde. *O que é o Programa Saúde na Escola (PSE)?* 2025.

SOUSA, M. C.; ESPERIDIÃO, M. A.; MEDINA, M. G. A intersetorialidade no PSE. *Ciência & Saúde Coletiva*, v. 22, n. 6, p. 1781-1790, 2017.
