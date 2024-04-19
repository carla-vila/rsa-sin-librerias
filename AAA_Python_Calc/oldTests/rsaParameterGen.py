import math

def format_number_for_c(num, variable_name, size):
    num_bits = num.bit_length()
    chunk_size_bits = 64
    num_chunks = (num_bits + chunk_size_bits - 1) // chunk_size_bits  

    chunks = []
    for i in range(num_chunks):
        chunk = (num >> (i * chunk_size_bits)) & ((1 << chunk_size_bits) - 1)
        chunks.append(chunk)

    chunks.reverse()  # Reverse chunks for little-endian format
    # Pad with zeros to match the specified size
    chunks += [0] * (size - len(chunks))

    # Generate C code
    c_code = f"uint64_t {variable_name}[{size}] = {{" + ", ".join(f"0x{chunk:x}" for chunk in chunks) + "};"
    return c_code

def format_message_for_c(msg, variable_name, size):
    return format_number_for_c(msg, variable_name, size)

# Provided primes
p = 802986252867975723492272689877
q = 979958270842649425028570265847
# Compute n (modulus)
m = p * q

# Compute phi (Euler's totient function)
phi = (p - 1) * (q - 1)

# Find e (public exponent)
e = 65537  # Typically 65537 is used for e
while math.gcd(e, phi) != 1 and e < phi:
    e += 1

# Compute d (private exponent) using Extended Euclidean Algorithm
def extended_gcd(aa, bb):
    lastremainder, remainder = abs(aa), abs(bb)
    x, lastx, y, lasty = 0, 1, 1, 0
    while remainder:
        lastremainder, (quotient, remainder) = remainder, divmod(lastremainder, remainder)
        x, lastx = lastx - quotient * x, x
        y, lasty = lasty - quotient * y, y
    return lastremainder, lastx * (-1 if aa < 0 else 1), lasty * (-1 if bb < 0 else 1)

gcd, x, y = extended_gcd(e, phi)
d = x % phi
if d < 0:
    d += phi  # Ensure d is positive

# Format numbers for C
c_formatted_m = format_number_for_c(m, "x", 20)
c_formatted_e = format_number_for_c(e, "e", 18)
c_formatted_d = format_number_for_c(d, "y", 20)
print(c_formatted_m)
print(c_formatted_e)
print(c_formatted_d)

# Example message and encryption/decryption
msg =  11
C = pow(msg, e, m)  # Encrypt
M = pow(C, d, m)    # Decrypt

# Format messages for C
c_formatted_msg = format_message_for_c(msg, "msg", 20)  # Original message in array format
c_formatted_enc = format_message_for_c(C, "enc", 20)    # Encrypted message in array format
c_formatted_dec = format_message_for_c(M, "dec", 20)    # Decrypted message in array format

print(c_formatted_msg)
print(f'Encrypted message: {c_formatted_enc}')
print(f'Decrypted message: {c_formatted_dec}')