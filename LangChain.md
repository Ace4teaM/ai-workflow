## Composants

LangChain est composé de plusieurs composants:

* **LangChain** : Permet d'**enchainer des appels** aux LLM avec abstraction du fournisseur
* **LangGraph** : Permet de créer des **graphe a états** exécutables
* **LangSmith** : Permet de tracer les échanges entre le LLM et le client

## Intégration

Peut être implémenté avec **Python** ou **Javascript**

## Généralités

LangChain est basé sur une hiérarchie d'objets exécutables

```
Runnable => Chain => Node => Graph
```

## Runnable

https://reference.langchain.com/python/langchain-core/runnables/base/Runnable

Une unité de travail qui peut être invoquée, par lots, en streaming, transformée et composée.

C'est la base de l'exécution de tâches, il sera utilisé dans les concepts suivants.

### Méthodes clés

- `invoke``ainvoke`/: Transforme une seule entrée en sortie.
- `batch``abatch`/: Transforme plusieurs entrées en une sortie.
- `stream``astream`/: Diffuse la sortie d'une seule entrée au fur et à mesure de sa production.
- `astream_log`: Flux de sortie et résultats intermédiaires sélectionnés à partir d'un entrée.

Optimisations intégrées:

- **Lot** : Par défaut, batch runs invoque() en parallèle à l'aide d'un pool de threads exécuteur testamentaire. Passez en trop pour optimiser le batching.
- **Async** : Méthodes avec  `'a'`Le préfixe est asynchrone. Par défaut, ils exécutent la contrepartie de synchronisation en utilisant le pool de threads d'asyncio. Remplacer pour l'async native.

Toutes les méthodes acceptent un argument de configuration optionnel, qui peut être utilisé pour configurer exécuter, ajouter des balises et des métadonnées pour le traçage et le débogage, etc.

Les exécutables exposent des informations schématiques sur leur entrée, leur sortie et leur configuration via les  `input_schema`propriété, le  `output_schema`propriété et  `config_schema`méthode.

### Composé

La composition permet d'enchainer ou paralléliser les appels aux unités de travails.

Soit en chaine (`RunnableSequence`) : Runnable 1 =>  Runnable 2 =>  Runnable 3 => ....

Soit en parallèle (`RunnableParallel`) : Runnable 1 |  Runnable 2 |  Runnable 3 | ...

 **`RunnableSequence`**invoque une série de runnables de manière séquentielle, avec une sortie de Runnable servant d'entrée suivante. Construire en utilisant les  `|`opérateur ou en passant une liste de runnables à `RunnableSequence`.

 **`RunnableParallel`**invoque des exécutables simultanément, fournissant la même entrée à chacun. Construire en utilisant un dict littéral dans une séquence ou en passant un dicte à `RunnableParallel`.

Par exemple,

```python
from langchain_core.runnables import RunnableLambda

# A RunnableSequence constructed using the `|` operator
sequence = RunnableLambda(lambda x: x + 1) | RunnableLambda(lambda x: x * 2)
sequence.invoke(1)  # 4
sequence.batch([1, 2, 3])  # [4, 6, 8]

# A sequence that contains a RunnableParallel constructed using a dict literal
sequence = RunnableLambda(lambda x: x + 1) | {
    "mul_2": RunnableLambda(lambda x: x * 2),
    "mul_5": RunnableLambda(lambda x: x * 5),
}
sequence.invoke(1)  # {'mul_2': 4, 'mul_5': 10}
```

### Méthodes standard

Tous `Runnable`est exposer des méthodes supplémentaires qui peuvent être utilisées pour modifier leur comportement (par exemple, ajouter une stratégie de réessai, ajouter des auditeurs du cycle de vie, les faire configurable, etc.).

Ces méthodes fonctionneront sur n'importe quelle `Runnable`, y compris  `Runnable`chaînes construit par la composition d'autres `Runnable`s. Voir les méthodes individuelles pour plus de détails.

Par exemple,

```python
from langchain_core.runnables import RunnableLambda

import random

def add_one(x: int) -> int:
    return x + 1

def buggy_double(y: int) -> int:
    """Buggy code that will fail 70% of the time"""
    if random.random() > 0.3:
        print('This code failed, and will probably be retried!')  # noqa: T201
        raise ValueError('Triggered buggy code')
    return y * 2

sequence = (
    RunnableLambda(add_one) |
    RunnableLambda(buggy_double).with_retry( # Retry on failure
        stop_after_attempt=10,
        wait_exponential_jitter=False
    )
)

print(sequence.input_schema.model_json_schema()) # Show inferred input schema
print(sequence.output_schema.model_json_schema()) # Show inferred output schema
print(sequence.invoke(2)) # invoke the sequence (note the retry above!!)
```

### Débogage et traçage

Comme les chaînes s'allongent, il peut être utile de pouvoir voir des résultats intermédiaires pour déboguer et tracer la chaîne.

Vous pouvez définir le drapeau de débogage global sur True pour activer la sortie de débogage pour toutes les chaînes:

```python
from langchain_core.globals import set_debug

set_debug(True)
```

Alternativement, vous pouvez passer des rappels existants ou personnalisés à n'importe quelle chaîne donnée:

```python
from langchain_core.tracers import ConsoleCallbackHandler

chain.invoke(..., config={"callbacks": [ConsoleCallbackHandler()]})
```

## Chain

 Une **chain** est simplement une “chaîne de traitement” qui prend une **entrée**, la transforme éventuellement (via un prompt, une fonction, un outil), puis envoie le tout au LLM et retourne la **réponse**.

### **BaseChain**

**Définition :**
 Une **chain** est simplement une “chaîne de traitement” qui prend une **entrée**, la transforme éventuellement (via un prompt, une fonction, un outil), puis envoie le tout au LLM et retourne la **réponse**.

- **Exemple classique :**

```
from langchain.chains import LLMChain
chain = LLMChain(llm=llm, prompt=prompt)
chain.run("Pourquoi le ciel est bleu ?")
```

- **Caractéristiques :**
  - Tu dois tout préparer toi-même (prompts, variables).
  - Pas de mémoire intégrée ni d’intelligence pour choisir un outil.
  - Simple et direct.

Usage : génération de texte directe à partir d’un prompt ou d’un template.

------

### **RetrievalQA** (RAG)

`RetrievalQA` est  de type `Chain` et indirectement `Runnable` vous pouvez donc l'ajouter dans une chaine d'exécution

**Définition :**
 Une **RetrievalQA** est une chain spécialisée qui combine **retrieval + LLM**.

- **Fonctionnement :**
  1. Tu as une **base de documents** (vector DB).
  2. Tu poses une **question**.
  3. LangChain **cherche les passages pertinents** via le retriever.
  4. Ces passages sont injectés dans le prompt (`{context}`).
  5. Le LLM génère une réponse basée sur ces documents.
- **Exemple :**

```python
from langchain.chains import RetrievalQA
qa = RetrievalQA.from_chain_type(llm=llm, retriever=retriever)
qa.invoke("Comment améliorer le scénario ?")
```

- **Caractéristiques :**
  - Automatiquement **contextualisé par les documents**.
  - La question et le contexte sont gérés par la chain.
  - Tu peux personnaliser le prompt via `chain_type_kwargs={"prompt": prompt}`.

Usage : tu veux que ton LLM utilise **une base de documents pour répondre**, sans tout injecter manuellement.

## Graph

https://docs.langchain.com/oss/python/langgraph/graph-api

Avec **LangGraph** vous pouvez encapsuler des enchainements d'appels (**LangChain**) dans des nœuds à état et ainsi créer des **graphes décisionnels**.

Ainsi un Graphe contient des nœuds ou sous-graphes et un nœud est exécutable (**Runnable**) dont il peut exécuter un **LangChain** ou tout autre instructions de code.

À la base, LangGraph modélise les flux de travail des  agents en tant que graphiques. Vous définissez le comportement de vos  agents en utilisant trois composants clés:

1. [`State`](https://docs.langchain.com/oss/python/langgraph/graph-api#state): Une structure de données partagée qui représente l'instantané actuel de votre application. Il peut être n'importe quel type de données, mais  est généralement défini à l'aide d'un schéma d'état partagé.
2. [`Nodes`](https://docs.langchain.com/oss/python/langgraph/graph-api#nodes): Fonctions qui encodent la logique de vos agents. Ils reçoivent l'état  actuel en entrée, effectuent un calcul ou un effet secondaire, et  retournent un état mis à jour.
3. [`Edges`](https://docs.langchain.com/oss/python/langgraph/graph-api#edges): Fonctions qui déterminent laquelle  `Node`pour exécuter ensuite en fonction de l'état actuel. Il peut s'agir de branches conditionnelles ou de transitions fixes.

### Noeuds

Un graphe est composé de nœuds (Nodes).

Lors d'un appel à `builder.add_node(name,node)` vous ajoutez un nœud de type `StateNode`

`StateNode` étant un `Runnable` vous pouvez l'ajouter dans une chaine d'exécution

https://reference.langchain.com/python/langgraph/graph/_node/StateNode

### **Agent**

Lors d'un appel à `create_agent(model,tools,...)` vous ajoutez créez un graph de type `CompiledStateGraph`

`CompiledStateGraph` étant un `StateNode` et donc un `Runnable` vous pouvez l'ajouter dans une  chaine d'exécution

Exemple,

https://reference.langchain.com/python/langchain/agents/factory/create_agent

```python
from langchain.agents import create_agent

# Crée un graphe d'agents qui appelle des outils en boucle jusqu'à ce qu'une condition d'arrêt soit remplie.
def check_weather(location: str) -> str:
    '''Return the weather forecast for the specified location.'''
    return f"It's always sunny in {location}"

graph = create_agent(
    model="anthropic:claude-sonnet-4-5-20250929",
    tools=[check_weather],
    system_prompt="You are a helpful assistant",
)

inputs = {"messages": [{"role": "user", "content": "what is the weather in sf"}]}
for chunk in graph.stream(inputs, stream_mode="updates"):
    print(chunk)
```

Un agent étant un graphe, il peut **raisonner, planifier, et appeler plusieurs tools ou chains** en fonction de la demande de l’utilisateur.

- **Fonctionnement :**
  1. Tu lui donnes **une liste d’outils/skills** (ex: `write_story`, `generate_enemy`).
  2. L’agent décide **automatiquement** quel outil utiliser et avec quelles entrées.
  3. L’agent peut faire plusieurs appels successifs (raisonnement étape par étape).
- **Exemple :**

```python
from langchain.agents import initialize_agent, AgentType

tools = [story_tool, enemy_tool]
agent = initialize_agent(tools, llm, agent=AgentType.ZERO_SHOT_REACT_DESCRIPTION)
agent.run("Crée un scénario et génère un ennemi dragon")
```

- **Caractéristiques :**
  - L’agent **raisonne et choisit l’action** à chaque étape.
  - Peut combiner plusieurs chains et outils.
  - Idéal pour les **agents complexes ou workflows multi-étapes**.

Usage : systèmes autonomes avec **plusieurs skills ou chaînes**, type “assistant créatif de jeu vidéo” ou “IA de développement logiciel”.