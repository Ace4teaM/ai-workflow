from langchain.tools import tool

@tool("read_text")
def read(filename:str):
    """Lit un fichier texte

    Args:
        filename: Nom du fichier à lire
    """

    try:
        with open(filename, "r") as f:
            return f.read()
    except Exception as e:
        return f"Erreur de l'écriture du fichier '{filename}': {e}"

tools = [read]