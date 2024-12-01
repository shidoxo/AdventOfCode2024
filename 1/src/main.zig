const std = @import("std");

pub fn main() !void {
    const file = try std.fs.cwd().openFile("input.txt", .{});
    defer file.close();

    var buf_reader = std.io.bufferedReader(file.reader());
    var in_stream = buf_reader.reader();

    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    const allocator = gpa.allocator();

    defer {
        const deinit_status = gpa.deinit();
        if (deinit_status == .leak) @panic("Memory leak detected!");
    }

    const contents = try in_stream.readAllAlloc(allocator, std.math.maxInt(usize));
    defer allocator.free(contents);

    var col1 = std.ArrayList(u32).init(allocator);
    defer col1.deinit();
    var col2 = std.ArrayList(u32).init(allocator);
    defer col2.deinit();

    var firstAnswer: u32 = 0;

    var line_iter = std.mem.splitScalar(u8, contents, '\n');

    while (line_iter.next()) |line| {
        if (line.len == 0) continue;

        var column_iter = std.mem.splitSequence(u8, line, "   ");

        if (column_iter.next()) |first| {
            const num1 = try std.fmt.parseInt(u32, first, 10);

            try col1.append(num1);

            if (column_iter.next()) |second| {
                const num2 = try std.fmt.parseInt(u32, second, 10);

                try col2.append(num2);
            }
        }
    }

    std.mem.sort(u32, col1.items, {}, comptime std.sort.asc(u32));
    std.mem.sort(u32, col2.items, {}, comptime std.sort.asc(u32));

    for (col1.items, col2.items) |num1, num2| {
        const diff = if (num1 > num2) num1 - num2 else num2 - num1;
        firstAnswer += diff;
    }

    std.debug.print("Answer to the first question: {}\n", .{firstAnswer});

    var secondAnswer: u32 = 0;

    for (col1.items) |num1| {
        var count: u32 = 0;
        for (col2.items) |num2| {
            if (num1 == num2) {
                count += 1;
            }
        }

        secondAnswer += num1 * count;
    }

    std.debug.print("Answer to the second question: {}\n", .{secondAnswer});
}
