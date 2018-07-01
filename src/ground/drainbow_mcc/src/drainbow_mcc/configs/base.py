import logging
from datetime import timedelta

# Общие настройки
LOG_LEVEL = logging.ERROR
""" уровень логгирования """

REDIS_URL = "redis://:@localhost:6379/0"
""" Адрес редис сервера """

# Настройки мавлинковской службы
# ==================================================

MAV_PLOT_DATA_PBACK = timedelta(seconds=120)
""" Интервал времени в течение которого будут хранится даннные телеметрии для отображения от "сейчас" """

MAV_LISTEN_URL = 'udpin:0.0.0.0:11000'
""" Адрес для mavutil, на котором служба будет слушать сообщения """

MAV_LOG_LEVEL = LOG_LEVEL
""" Уровень логирования демона """


# Настройки службы, которая дефрагментирует мавлинковые пакеты
# ==================================================
MAV_DEFRAG_LISTEN_URL = 'udpin:0.0.0.0:10000'
""" адрес для приёма фрагментированных пакетов
    передаются пакеты в  MAV_LISTEN_URL.replace("in", "out")
"""

MAV_DEFRAG_REPORT_PERIOD = 1.0
""" Частота отчетов в лог дефрагментатора в секундах
    (не чаще этого значения и не чаще таймаута, если соообщений нет )
"""

MAV_DEFRAG_RECEIVE_TIMEOUT = 1.0
""" таймаут приема сообщения на входщем мавлик коннекшоне в секундах """

MAV_DEFRAG_LOG_LEVEL = logging.INFO
""" Уровень лога службы """

# Настройки веб службы
# ==================================================
WEB_LOG_LEVEL = LOG_LEVEL

PLOT_DATA_UPDATE_PERIOD_MS = 500
""" период обновления графиков (в мс) """

MODEL_DATA_UPDATE_PERIOD_MS = 100
""" период обновления модели (в мс) """

SPECTRUM_DATA_UPDATE_PERIOD_MS = 1000
""" период обновления модели (в мс) """

IMU_PLOT_SCOPE_MS = timedelta(seconds=15)
""" Диапазон отображения на графике последних данных MPU6000 """

PRESSURE_PLOT_SCOPE_MS = timedelta(seconds=15)
""" Диапазон отображения на графике последних данных MPU6000 """

MAP_PLOT_SCOPE_MS = timedelta(seconds=15)
""" Диапазон отображения на графике последних данных MPU6000 """

DISTANCE_PLOT_SCOPE_MS = timedelta(seconds=15)
""" Диапазон отображения на графике последних данных MPU6000 """

# Настройки стриминга звука
# ==================================================
SOUND_CHANNELS = 1
""" Количество каналов звукового потока """

SOUND_RATE = 44100
""" Частота дискретизации звукового потока """

SOUND_CHUNK = 1024
""" Размер сегмента звукового потока """

SOUND_UDP_PORT = 23576
""" Порт для приёма звука с борта """

SOUND_TCP_PORT = 23578
""" Порт для пересылки звука на сервере """
