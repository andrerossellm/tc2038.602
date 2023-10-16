from sais import sais
import os.path
from time import time
from guppy import hpy

def menu():
    print("*****SELECCIONE LIBRO POR CARGAR*****")
    print("1. Metamórfosis de Franz Kafka")
    print("2. La Ilíada de Homero")
    print("3. La República de Platón")
    print("4. Las Aventuras de Tom Sawyer de Mark Twain")
    print("5. Memorias del Subsuelo de Dostoyevski")
    print("0. Terminar ejecución")
    print("*****ESCRIBA NÚMERO DE SU ELECCIÓN*****")
    try:
        choi = int(input("> "))
        while(choi < 0 or choi > 5):
            choi = int(input("Escriba un número válido"))
    except:
        print("\nALERTA: Input inválido")
        print()
        print()
        print()
        choi = menu()
    return choi

def search(text, SA, query):
    n = len(text)
    m = len(query)
    occurrences = []

    left, right = 0, n - 1

    while left <= right:
        mid = (left + right) // 2
        suffix = text[SA[mid]:SA[mid] + m]

        if query == suffix:
            # Found a match, append it to the list of occurrences
            occurrences.append(SA[mid])
            
            # Continue searching to the right
            i = mid + 1
            while i < n and text[SA[i]:SA[i] + m] == query:
                occurrences.append(SA[i])
                i += 1

            # Continue searching to the left
            i = mid - 1
            while i >= 0 and text[SA[i]:SA[i] + m] == query:
                occurrences.append(SA[i])
                i -= 1

            break
        elif query > suffix:
            left = mid + 1
        else:
            right = mid - 1

    return sorted(occurrences)

def readFile(optn):
    filename = os.path.dirname(os.path.realpath(__file__)) + "/resources/"
    if optn == 1:
        filename += "metamorphosis.txt"
    elif optn == 2:
        filename += "theiliad.txt"
    elif optn == 3:
        filename += "therepublic.txt"
    elif optn == 4:
        filename += "tomsawyer.txt"
    elif optn == 5:
        filename += "underground.txt"
    with open(filename, 'r', encoding='utf-8') as file:
        string = file.read().split()
    string = "_".join(string) + "$"
    return string[1:]

def main():
    while True:
        choi = menu()
        if choi == 0:
            break
        
        h = hpy()
        start = time()
        
        string = readFile(choi)
        T = [ord(c) for c in string]
        SA = sais(T)


        end = time()
        elTime = end - start
        #print(SA)
        
        
        query = str(input("Texto a buscar: "))
        query = query.split()
        query = "_".join(query)
        occurrences = search(string, SA, query)
        print("Occurrences of '{}': {}".format(query, occurrences))
        
        print("\n")
        print(f'*****TELEMETRIA DE LIBRO {choi}*****')
        print(h.heap())
        print(f'Tiempo de ejecución: {elTime} s')
        print("\n\n")
        with open("pythonTelemetry.txt", "a") as f:
            print(f'*****TELEMETRIA DE LIBRO {choi}*****', file = f)
            print(h.heap(), file = f)
            print(f'Tiempo de ejecución: {elTime} s', file = f)
            print("\n", file = f)


main()
