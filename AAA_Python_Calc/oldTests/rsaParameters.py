import math

def format_number_for_c(num, variable_name):
    num_bits = num.bit_length()
    chunk_size_bits = 64
    num_chunks = (num_bits + chunk_size_bits - 1) // chunk_size_bits  

    chunks = []
    for i in range(num_chunks):
        chunk = (num >> (i * chunk_size_bits)) & ((1 << chunk_size_bits) - 1)
        chunks.append(chunk)

    chunks.reverse()  # Chunks should be added in reverse order for little-endian format

    # Generate C code
    c_code = f"uint64_t {variable_name}[{len(chunks)}] = {{" + ", ".join(hex(chunk) for chunk in chunks) + "};"
    return c_code

# Provided primes
p = 1933444428977608466756180558194762820167372506897218560547529754741061194840028701037986917855978086583664570217376795751415921659713544179764948508217
q = 1841410092846780887722814972821980809393460847986984087041074481345101505628755686647482712526273544742704826709967363649997568225819535167618432003183

# Step 2: Compute n (modulus)
m = p * q
print("m =", m)

# Print formatted m for C
c_formatted_m = format_number_for_c(m, "m")
print(c_formatted_m)

# Step 3: Compute phi (Euler's totient function)
phi = (p - 1) * (q - 1)

# Step 4: Find e (public exponent)
e = 2
while e < phi:
    if math.gcd(e, phi) == 1:
        break
    e += 1
print("e =", e)

# Format e for C
c_formatted_e = format_number_for_c(e, "e")
print(c_formatted_e)

# Step 5: Find d (private exponent) using Extended Euclidean Algorithm
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
    d += phi  # ensure d is positive

print("d =", d)

# Format d for C
c_formatted_d = format_number_for_c(d, "d")
print(c_formatted_d)

print(f'Public key: ({e}, {m})')
print(f'Private key: ({d}, {m})')

# Plain text
msg = 11
print(f'Original message: {msg}')

# Encryption using modular exponentiation
C = pow(msg, e, m)
print(f'Encrypted message: {C}')

# Decryption
M = pow(C, d, m)
print(f'Decrypted message: {M}')