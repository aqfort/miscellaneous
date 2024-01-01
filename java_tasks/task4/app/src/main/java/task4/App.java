package task4;

import java.util.Objects;

import io.netty.bootstrap.Bootstrap;
import io.netty.buffer.Unpooled;
import io.netty.channel.ChannelFuture;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.ChannelInitializer;
import io.netty.channel.EventLoopGroup;
import io.netty.channel.SimpleChannelInboundHandler;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.nio.NioDatagramChannel;
import io.netty.handler.codec.dns.DatagramDnsQuery;
import io.netty.handler.codec.dns.DatagramDnsQueryDecoder;
import io.netty.handler.codec.dns.DatagramDnsResponse;
import io.netty.handler.codec.dns.DatagramDnsResponseEncoder;
import io.netty.handler.codec.dns.DefaultDnsQuestion;
import io.netty.handler.codec.dns.DefaultDnsRawRecord;
import io.netty.handler.codec.dns.DnsRecordType;
import io.netty.handler.codec.dns.DnsResponseCode;
import io.netty.handler.codec.dns.DnsSection;
import io.netty.util.internal.SocketUtils;

public class App {

    public String getGreeting() {
        return "Hello!!!";
    }

    static void usage() {
        System.err.println("java App <IP> <PORT>\n\n"
                + "it doesn't have good input parser\n"
                + "serves only \"example.com\"\n"
                + "correct input style:\n"
                + "\tIP: 127.0.0.1\n"
                + "\tPORT: 7000\n\n"
                + "test:\n"
                + "\tnslookup -port=<PORT> example.com <IP>");
        System.exit(-1);
    }

    public static void main(String[] args) {
        System.out.println(new App().getGreeting());

        if (args.length != 2)
            usage();

        try {
            Server server = new Server(args[0], Integer.parseInt(args[1]));
            server.runServer();
        } catch (Exception exception) {
            System.out.println(exception.getMessage());
        }
    }
}

class Server {

    private String ip = "127.0.0.1";
    private Integer port = 7000;

    public Server(String ip, Integer port) {
        this.ip = ip;
        this.port = port;
    }

    public void runServer() {
        EventLoopGroup eventLoopGroup = new NioEventLoopGroup();
        try {
            Bootstrap bootstrap = new Bootstrap();
            bootstrap.group(eventLoopGroup)
                    .channel(NioDatagramChannel.class)
                    .handler(new ChannelInitializer<NioDatagramChannel>() {
                        @Override
                        public void initChannel(NioDatagramChannel channel) throws Exception {
                            channel.pipeline().addLast(new DatagramDnsQueryDecoder());
                            channel.pipeline().addLast(new DatagramDnsResponseEncoder());
                            channel.pipeline().addLast(new DNSHandler());
                        }
                    });
            ChannelFuture channelFuture = bootstrap.bind(port).sync();
            System.out.println("Server is listening on port: " + port);
            channelFuture.channel().closeFuture().sync();
        } catch (InterruptedException interruptedException) {
            System.out.println(interruptedException.getMessage());
        } finally {
            eventLoopGroup.shutdownGracefully();
            System.out.println("Server has been shut down");
        }
    }

    private class DNSHandler extends SimpleChannelInboundHandler<DatagramDnsQuery> {

        @Override
        protected void channelRead0(ChannelHandlerContext ctx, DatagramDnsQuery msg) throws Exception {
            DatagramDnsResponse response = new DatagramDnsResponse(msg.recipient(), msg.sender(), msg.id());
            DefaultDnsQuestion question = msg.recordAt(DnsSection.QUESTION);
            response.addRecord(DnsSection.QUESTION, question);
            byte[] address = SocketUtils.addressByName(ip).getAddress();
            if (Objects.equals(question.name(), "example.com.")) {
                DefaultDnsRawRecord answer = new DefaultDnsRawRecord(question.name(), DnsRecordType.A, 3600,
                        Unpooled.wrappedBuffer(address));
                response.addRecord(DnsSection.ANSWER, answer);
                ctx.writeAndFlush(response);
            } else {
                response.setCode(DnsResponseCode.BADNAME);
                ctx.writeAndFlush(response);
            }
        }
    }
}
