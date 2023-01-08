import spdlog as spd
# logger = spd.FileLogger('fast_logger', '/tmp/spdlog_example.log')
# logger.set_level(spd.LogLevel.INFO)
logger = spd.ConsoleLogger('console_logger', True, True, True)
# logger.set_level(spd.LogLevel.DEBUG)
logger.info('Hello World!')
logger.debug('I am not so important.')
logger.warn('warn here.')
logger.error('error here')
