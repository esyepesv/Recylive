from django.shortcuts import render
from django.http import HttpResponse
from django.db import models
from pagina.models import Residente
import csv



def home(request):
    #leerDatos()
    return render(request, 'home.html')

#leer datos y actualizar bd
def leerDatos():
    file = open("C:/Users/estiv/OneDrive/Escritorio/P1/Recylive project/hardware/datos.csv")
    csvreader = csv.reader(file)
    header = next(csvreader)
    rows = []
    for row in csvreader:
        actualizarBD(row[0], pesoAPuntos(int(row[1])))
    file.close()

def actualizarBD(ID, puntos):
    residente = Residente.objects.filter(carnet=ID).first()
    residente.puntos += puntos
    residente.save()
    

def pesoAPuntos(peso):
    #cada 100 gramos es 1 punto
    puntos = int(peso/100)
    return puntos

#vistas de premios y residentes
def premios(request): 
    return render(request, 'premios.html')

def residentes(request): 
    return render(request, 'residentes.html')
