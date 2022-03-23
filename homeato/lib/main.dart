import 'package:flutter/material.dart';
import 'package:webview_flutter/webview_flutter.dart';

void main() => runApp(const MainApp());

class MainApp extends StatelessWidget {
  const MainApp({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: "HOMEATO",
      home: Scaffold(
          appBar: AppBar(
          title: const Center(
            child: Text("HOMEATO"),
          ),
        ),
        body: const WebView(
          initialUrl: "http://192.168.2.2/HomeAutomation/index.php",
          javascriptMode: JavascriptMode.unrestricted,
        ),
      ),
    );
  }
}
