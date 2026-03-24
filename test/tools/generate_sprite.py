import base64
import requests
from langchain.agents import initialize_agent, Tool
from langchain.agents import AgentType
from langchain_openai import ChatOpenAI
from openai import OpenAI

client = OpenAI()


def generate_sprite(prompt: str) -> str:
    """
    Génère un sprite et l'enregistre dans un fichier PNG.
    input = description du sprite
    """

    result = client.images.generate(
        model="gpt-image-1",
        prompt=f"pixel art sprite sheet style, game sprite, transparent background: {prompt}",
        size="512x512"
    )

    image_base64 = result.data[0].b64_json
    image_bytes = base64.b64decode(image_base64)

    filename = "sprite.png"

    with open(filename, "wb") as f:
        f.write(image_bytes)

    return f"Sprite généré et sauvegardé dans {filename}"


tools = [
    Tool(
        name="SpriteGenerator",
        func=generate_sprite,
        description="Génère un sprite pixel art pour jeu vidéo à partir d'une description"
    )
]

def test():
    llm = ChatOpenAI(temperature=0)

    agent = initialize_agent(
        tools,
        llm,
        agent=AgentType.ZERO_SHOT_REACT_DESCRIPTION,
        verbose=True
    )
    
    agent.run("génère un sprite pixel art d'un dragon rouge pour jeu vidéo")