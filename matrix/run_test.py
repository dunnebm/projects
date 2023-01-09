import numpy as np
import re
import socket
from io import StringIO

def formatResult(arg):
  result = np.array2string(arg, separator=',', max_line_width=2**31 - 1)
  result = re.sub(remove_brackets, "", result)
  result = re.sub(remove_line_ending_commas, "", result)
  return "<matrix>\n" + result + "</matrix>"

def testAddition(args):
  if len(args) != 2:
    return "<error>Invalid number of arguments</error>"
  result = np.zeros(1)
  if isinstance(args[1], float):
    result = args[0] + args[1]
  elif isinstance(args[1], np.ndarray):
    result = np.add(args[0], args[1])
  return formatResult(result)

def testSubtraction(args):
  if len(args) != 2:
    return "<error>Invalid number of arguments</error>"
  result = args[0] - args[1]
  return formatResult(result)

def testMultiplication(args):
  if len(args) != 2:
    return "<error>Invalid number of arguments</error>"
  result = np.zeros(1)
  if isinstance(args[1], float):
    result = args[0] * args[1]
  elif isinstance(args[1], np.ndarray):
    result = np.matmul(args[0], args[1])
  return formatResult(result)

def testDivision(args):
  if len(args) != 2:
    return "<error>Invalid number of arguments</error>"
  result = args[0] / args[1]
  return formatResult(result)

def testInverse(args):
  if len(args) != 1:
    return "<error>Invalid number of arguments</error>"
  result = np.linalg.inv(args[0])
  return formatResult(result)

def testDeterminant(args):
  if len(args) != 1:
    return "<error>Invalid number of arguments</error>"
  result = np.linalg.det(args[0])
  return "<scalar> " + str(result) + "</scalar>"

def parseArgs(str):
  matches = arg_pattern.finditer(str)
  args = list();
  for match in matches:
    if match.group(1) == "matrix":
      args.append(np.genfromtxt(StringIO(match.group(2)), dtype=np.float64, delimiter=','))
    elif match.group(1) == "scalar":
      args.append(float(match.group(2)))
  return args

def executeRequest(data):
  matches = op_pattern.finditer(data.decode())
  for match in matches:
    args = parseArgs(match.group(2))
    if match.group(1) == "add":
      return  testAddition(args)
    elif match.group(1) == "sub":
      return testSubtraction(args)
    elif match.group(1) == "mul":
      return testMultiplication(args)
    elif match.group(1) == "div":
      return testDivision(args)
    elif match.group(1) == "inv":
      return  testInverse(args)
    elif match.group(1) == "det":
      return testDeterminant(args)
    elif match.group(1) == "exit":
      return "exit"
    else:
      return "<error> Invalid operation </error>"
  return "<error> Invalid Format </error>"


if __name__ == '__main__':
  op_pattern = re.compile(r'<(add|sub|mul|div|inv|det|exit)>([\.\s\w\d<>/,-]*?)</\1>')
  arg_pattern = re.compile(r'<(matrix|scalar)>([\.\s\d,-]*?)</\1>')
  remove_brackets = re.compile(r'[\[\]]+')
  remove_line_ending_commas = re.compile(r',(?=\n)')
  host = "127.0.0.1"
  port = 55555

  sock = socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM)
  sock.bind((host, port))
  sock.listen()

  conn, addr = sock.accept()

  sock.close()

  while True:
    data = conn.recv(4096)
    if len(data) != 0:
      result = executeRequest(data)
      if result == "exit":
        break;
      conn.sendall(bytes(result, 'utf-8'))
  
  print("Exiting")
  conn.close()