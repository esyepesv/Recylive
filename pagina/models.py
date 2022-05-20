from django.db import models

# Create your models here.

class Residente(models.Model):
    nombre = models.CharField(max_length=100)
    apartamento = models.CharField(max_length=50)
    cedula = models.IntegerField()
    telefono = models.IntegerField()
    carnet = models.CharField(max_length=50)
    puntos = models.IntegerField(blank=True)

class Premios(models.Model):
    premio = models.CharField(max_length=100)
    puntos_necesarios = models.IntegerField()
