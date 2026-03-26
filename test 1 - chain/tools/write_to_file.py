from langchain.tools import tool

@tool("write_to_file")
def write(filename:str, text: str):
    """Ecrit un texte dans un fichier

    Args:
        filename: Nom du fichier dans lequel écrire le texte
        text: Texte à écrire dans le fichier
    """

    try:
        with open(filename, "w") as f:
            f.write(text)
        # message de retour tracé dans la discution avec le LLM
        return f"Ecriture du fichier '{filename}'"
    except Exception as e:
        return f"Erreur lors de l'écriture du fichier '{filename}': {e}"

tools = [write]