# Generated by Django 4.0.2 on 2022-05-12 16:34

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Premios',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('premio', models.CharField(max_length=100)),
                ('puntos_necesarios', models.IntegerField()),
            ],
        ),
        migrations.CreateModel(
            name='Residente',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('nombre', models.CharField(max_length=100)),
                ('apartamento', models.CharField(max_length=50)),
                ('cedula', models.IntegerField()),
                ('telefono', models.IntegerField()),
                ('carnet', models.CharField(max_length=50)),
                ('puntos', models.IntegerField(blank=True)),
            ],
        ),
    ]