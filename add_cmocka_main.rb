#! ruby

def modify(file_name)
  puts "modifying #{file_name}"
  lines = load(file_name)
  middle = lines.
    find_all { |line| line =~ /static void (\w+)\(void\*\* state\)/ }.
    map { |line| line =~ /static void (\w+)\(void\*\* state\)/; $1 }.
    map { |name| "        cmocka_unit_test(#{name}), /* */\n" }.
    join()

  prefix = <<H1

int main(void)
{
    const struct CMUnitTest test_suite[] = {
H1
#  cmocka_unit_test(test_read_from_hardware), /* */
  postfix = <<H2
    };

    return cmocka_run_group_tests(test_suite, NULL, NULL);
}
H2
  main = prefix + middle + postfix
  append(file_name, main)
end

def load(file_name)
  IO.readlines(file_name)
end

def append(file_name, text)
  File.open(file_name, "a") do |file|
    file.print text
  end
end

if __FILE__ == $0

  Dir.chdir('src')

  # comment session files
  Dir['about_*.c'].each do |file_name|
    modify(file_name)
  end

  Dir.chdir('..')

end
