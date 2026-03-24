
def read(filename:str) -> str:
    with open(filename, "r") as f:
        return f.read()


tools = [
    Tool(
        name="read_text",
        func=read,
        description="Lit un texte depuis un fichier"
    )
]