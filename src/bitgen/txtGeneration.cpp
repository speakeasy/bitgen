/**
 * txtGeneration.cpp - Bitcoin address generator
 *
 * Copyright (C)2015 The bitgen developers <bitgen@openmailbox.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */
 
/**
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
*/


#include "txtGeneration.h"
#include "util.h"
#include "FileUtil.h"
#include "currencySpecific.h"


#include <iostream>










FilePair generateExtendedTxtFiles(const std::string& pub, const std::string priv, 
					const std::string& genMethod, 
					const std::string& thetime, const std::string& accountName,
					const std::string& versionNumber, const std::string& applicationName,
					const std::list<ExtraInfo>& generationExtra,
					const std::string& derivationPath,
					const bool currencySpecific
					)
{
	
	std::string pubTxt;

	if(currencySpecific)
	{
		pubTxt += "Currency         : ";
		const std::string currencyName = getCurrencyName();	
		pubTxt += currencyName;
		pubTxt += "\n";
	}
	
	pubTxt += "Public           : ";
	pubTxt += pub;
	pubTxt += "\n";
	
	pubTxt += "Generated by     : ";
	pubTxt += applicationName;
	pubTxt += " ";
	pubTxt += versionNumber;
	pubTxt += "\n";
	
	pubTxt += "Generation time  : ";
	pubTxt += thetime;
	pubTxt += "\n";
	if(!accountName.empty())
	{
		pubTxt += "Account name     : ";
		pubTxt += accountName;
		pubTxt += "\n";	
	}

	pubTxt += "Derivation path  : ";
	pubTxt += derivationPath;
	pubTxt += "\n";
	
	std::string privTxt(pubTxt);
	
	privTxt += "Private          : ";
	privTxt += priv;
	privTxt += "\n";
	
	privTxt += "Generation method: ";
	privTxt += genMethod;
	privTxt += "\n";

	//privTxt += "Mnemonic         : ";
	//privTxt += mnemonic;
	//privTxt += "\n";

// minSize(std::string str, const int minSize, const bool right = false);


	for(std::list<ExtraInfo>::const_iterator it = generationExtra.begin() ;
		it != generationExtra.end() ;
		++it)
	{
		const ExtraInfo& extra = (*it);
		privTxt += minSize(extra.title, 17);
		privTxt += ": ";
		privTxt += extra.value;
		privTxt += "\n";
		
	}

	//if(!generationExtra.empty())
	//{
	//	privTxt += "\n";
	//}


	FilePair fpair(pubTxt, privTxt);
	return fpair;
}







FilePair generateMnemonicFile(
					const std::string& genMethod, const std::list<ExtraInfo>& generationExtra,
					const std::string& thetime, const std::string& accountName,
					const std::string& mnemonic,
					const std::string& versionNumber, const std::string& applicationName,
					const bool currencySpecific,
					const std::string& xpriv, 
					const std::string& xpub,
					const std::string& derivedXpub,					
					const bool includedExtendedAddress,
					const int numWords)
{
	
	std::string pubTxt;

	if(currencySpecific || !derivedXpub.empty())
	{
		pubTxt += "Currency         : ";
		const std::string currencyName = getCurrencyName();	
		pubTxt += currencyName;
		pubTxt += "\n";
	}
		
	pubTxt += "Generated by     : ";
	pubTxt += applicationName;
	pubTxt += " ";
	pubTxt += versionNumber;
	pubTxt += "\n";
	
	pubTxt += "Generation time  : ";
	pubTxt += thetime;
	pubTxt += "\n";
	if(!accountName.empty())
	{
		pubTxt += "Account name     : ";
		pubTxt += accountName;
		pubTxt += "\n";	
	}

	if(includedExtendedAddress)
	{
		pubTxt += "xpub             : ";
		pubTxt += xpub;
		pubTxt += "\n";

		if(!derivedXpub.empty())
		{
			pubTxt += "derived xpub     : ";
			pubTxt += derivedXpub;
			pubTxt += "\n";
		}
	}

	pubTxt += "Num words        : ";
	pubTxt += intToString(numWords);
	pubTxt += "\n";

	
	std::string privTxt(pubTxt);
	
	privTxt += "Generation method: ";
	privTxt += genMethod;
	privTxt += "\n";

	privTxt += "Mnemonic         : ";
	privTxt += mnemonic;
	privTxt += "\n";

	if(includedExtendedAddress)
	{
		privTxt += "xpriv            : ";
		privTxt += xpriv;
		privTxt += "\n";
	}


	for(std::list<ExtraInfo>::const_iterator it = generationExtra.begin() ;
		it != generationExtra.end() ;
		++it)
	{
		const ExtraInfo& extra = (*it);
		privTxt += minSize(extra.title, 17);
		privTxt += ": ";
		privTxt += extra.value;
		privTxt += "\n";		
	}

	const FilePair filePair(pubTxt, privTxt);


	return filePair; //privTxt;
}









FilePair generateTxtFiles(const std::string& pubkey, const std::string privateb58, 
					const std::string& genMethod, const std::list<ExtraInfo>& generationExtra,
					const std::string& thetime, const std::string& accountName,
					const std::string& mnemonic, const bool compressed, 
					const std::string& versionNumber, const std::string& applicationName)
{
	
	std::string pubTxt;

	pubTxt += "Currency         : ";
	const std::string currencyName = getCurrencyName();	
	pubTxt += currencyName;
	pubTxt += "\n";
	
	pubTxt += "Public address   : ";
	pubTxt += pubkey;
	pubTxt += "\n";
	
	pubTxt += "Generated by     : ";
	pubTxt += applicationName;
	pubTxt += " ";
	pubTxt += versionNumber;
	pubTxt += "\n";
	
	pubTxt += "Generation time  : ";
	pubTxt += thetime;
	pubTxt += "\n";
	if(!accountName.empty())
	{
		pubTxt += "Account name     : ";
		pubTxt += accountName;
		pubTxt += "\n";	
	}

	
	std::string privTxt(pubTxt);
	
	privTxt += "Private key (WIF): ";
	privTxt += privateb58;
	privTxt += "\n";
	privTxt += "Compressed       : ";
	privTxt += (compressed ? "yes" : "no");
	privTxt += "\n";
	
	//if(!accountName.empty())
	//{
	//	privTxt += "Account name     : ";
	//	privTxt += accountName;
	//	privTxt += "\n";	
	//}
	privTxt += "Generation method: ";
	privTxt += genMethod;
	privTxt += "\n";

	privTxt += "Mnemonic         : ";
	privTxt += mnemonic;
	privTxt += "\n";



	for(std::list<ExtraInfo>::const_iterator it = generationExtra.begin() ;
		it != generationExtra.end() ;
		++it)
	{
		const ExtraInfo& extra = (*it);
		privTxt += minSize(extra.title, 20);
		
		privTxt += "::: ";
		privTxt += extra.value;
	}

	if(!generationExtra.empty())
	{
		privTxt += "\n";
	}


	FilePair fpair(pubTxt, privTxt);
	return fpair;
}




void saveExtendedTxtFiles(FilePair& txtFiles, const std::string& fileId, const bool currencySpecific)
{	
	std::string currencySpecStr;
	if(currencySpecific)
	{
		currencySpecStr += getCurrencyShortName();
		currencySpecStr += "_";		
	}
	
	const std::string pubFilename = "extended_" + currencySpecStr + fileId + "_share.txt";
	const std::string privFilename = "extended_" + currencySpecStr + fileId + "_private.txt";

	//const std::string fullPrivPath = (privPath == ".") ? privFilename : (privPath + "/" + privFilename);
	std::cout << "Saving priv txt: " << privFilename << std::endl;
	fileWrite(privFilename, txtFiles.privateFile);	

	//const std::string fullPubPath = (pubPath == ".") ? pubFilename : (pubPath + "/" + pubFilename);
	std::cout << "Saving pub txt : " << pubFilename << std::endl;
	fileWrite(pubFilename, txtFiles.publicFile);	
}





void saveTxtFiles(const std::string& pubkey, const std::string privateb58, 
					const std::string& genMethod, const std::list<ExtraInfo>& generationExtra,
					const std::string& thetime, const std::string& accountName,
					const std::string& mnemonic, const bool compressed, const std::string pubPath, const std::string privPath,
					const std::string& versionNumber, const std::string& applicationName)
{
	FilePair txtFiles = generateTxtFiles(pubkey, privateb58, genMethod, generationExtra,
					thetime, accountName, mnemonic, compressed,
					versionNumber, applicationName);
		
		
	const std::string pubFilename = pubkey + "_share.txt";
	const std::string privFilename = pubkey + "_private.txt";

	const std::string fullPrivPath = (privPath == ".") ? privFilename : (privPath + "/" + privFilename);
	std::cout << "Saving priv txt: " << fullPrivPath << std::endl;
	fileWrite(fullPrivPath, txtFiles.privateFile);	

	const std::string fullPubPath = (pubPath == ".") ? pubFilename : (pubPath + "/" + pubFilename);
	std::cout << "Saving pub txt : " << fullPubPath << std::endl;
	fileWrite(fullPubPath, txtFiles.publicFile);	
}








TxtInfoFile getTxtFiles(const std::string& pubkey, const std::string privateb58, 
					const std::string& genMethod, const std::list<std::string>& generationExtra,
					const std::string& thetime, const std::string& accountName,
					const std::string& mnemonic, const bool compressed,
					const std::string& versionNumber, const std::string& applicationName)
{
	std::string pubTxt;

	pubTxt += "Currency         : ";
	
	const std::string currencyName = getCurrencyName();	
	pubTxt += currencyName;

	pubTxt += "\n";
	
	pubTxt += "Public address   : ";
	pubTxt += pubkey;
	pubTxt += "\n";
	
	pubTxt += "Generated by     : ";
	pubTxt += applicationName;
	pubTxt += " ";	
	pubTxt += versionNumber;
	pubTxt += "\n";
	
	pubTxt += "Generation time  : ";
	pubTxt += thetime;
	pubTxt += "\n";
	if(!accountName.empty())
	{
		pubTxt += "Account name     : ";
		pubTxt += accountName;
		pubTxt += "\n";	
	}

	
	//const std::string pubFilename = pubkey + "_share.txt";
	//std::cout << "Saving pub txt : " << pubFilename << std::endl;
	//fileWrite(pubFilename, pubTxt);	
	
	
	
	std::string privTxt(pubTxt);
	
	privTxt += "Private key (WIF): ";
	privTxt += privateb58;
	privTxt += "\n";
	//privTxt += "Public address   : ";
	//privTxt += pubkey;
	//privTxt += "\n";
	//privTxt += "Generation time  : ";
	//privTxt += thetime;
	//privTxt += "\n";
	privTxt += "Compressed       : ";
	privTxt += (compressed ? "yes" : "no");
	privTxt += "\n";
	
	if(!accountName.empty())
	{
		privTxt += "Account name     : ";
		privTxt += accountName;
		privTxt += "\n";	
	}
	privTxt += "Generation method: ";
	privTxt += genMethod;
	privTxt += "\n";

	privTxt += "Mnemonic         : ";
	privTxt += mnemonic;
	privTxt += "\n";



	for(std::list<std::string>::const_iterator it = generationExtra.begin() ;
		it != generationExtra.end() ;
		++it)
	{
		const std::string& extra = (*it);
		privTxt += extra;
	}

	if(!generationExtra.empty())
	{
		privTxt += "\n";
	}


	const TxtInfoFile fileInfo(pubTxt, privTxt);
	return fileInfo;
	
	//const std::string privFilename = pubkey + "_private.txt";
	//std::cout << "Saving priv txt: " << privFilename << std::endl;
	//fileWrite(privFilename, privTxt);	

}


