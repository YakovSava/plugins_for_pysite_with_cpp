from plugins.compiler import compile as _compile
from plugins.app import Runner

_compile()

if __name__ == '__main__':
	runner = Runner(mode=1)
	runner.run()