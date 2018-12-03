using System;
using System.Xml.Serialization;
using System.Collections.Generic;

namespace Xml2CSharp
{
	[XmlRoot(ElementName="CameraParams")]
	public class CameraParams {
		
		[XmlElement(ElementName="K00")]
		public int K00 { get; set; }
		[XmlElement(ElementName="K01")]
		public int K01 { get; set; }
		[XmlElement(ElementName="K02")]
		public int K02 { get; set; }
		
		[XmlElement(ElementName="K10")]
		public int K10 { get; set; }
		[XmlElement(ElementName="K11")]
		public int K11 { get; set; }
		[XmlElement(ElementName="K12")]
		public int K12 { get; set; }
		
		[XmlElement(ElementName="K20")]
		public int K20 { get; set; }
		[XmlElement(ElementName="K21")]
		public int K21 { get; set; }
		[XmlElement(ElementName="K22")]
		public int K22 { get; set; }
		
		[XmlElement(ElementName="D0")]
		public int D0 { get; set; }
		[XmlElement(ElementName="D1")]
		public int D1 { get; set; }
		[XmlElement(ElementName="D2")]
		public int D2 { get; set; }
		[XmlElement(ElementName="D3")]
		public int D3 { get; set; }
		[XmlElement(ElementName="D4")]
		public int D4 { get; set; }
		[XmlElement(ElementName="D5")]
		public int D5 { get; set; }
		[XmlElement(ElementName="D6")]
		public int D6 { get; set; }
		[XmlElement(ElementName="D7")]
		public int D7 { get; set; }
		
	}

	[XmlRoot(ElementName="opencv_storage")]
	public class Opencv_storage {
		[XmlElement(ElementName="CameraParams")]
		public CameraParams CameraParams { get; set; }
	}

}
