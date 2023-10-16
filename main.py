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
        #print(SA)
        
        end = time()
        elTime = end - start
        print("\n")
        print(f'*****TELEMETRIA DE LIBRO {choi}*****')
        print(h.heap())
        print(f'Tiempo de ejecución: {elTime}')
        print("\n\n")
        with open("pythonTelemetry.txt", "a") as f:
            print(f'*****TELEMETRIA DE LIBRO {choi}*****', file = f)
            print(h.heap(), file = f)
            print(f'Tiempo de ejecución: {elTime}', file = f)
            print("\n", file = f)


main()
