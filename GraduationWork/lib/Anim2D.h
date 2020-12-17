#pragma once
#include <vector>
#include <string>

class ImageRenderer;

class Anim2D {
public:
	Anim2D(ImageRenderer* _renderer);
	~Anim2D();

	/// <summary>
	/// アニメーションの初期化
	/// </summary>
	void Start();

	/// <summary>
	/// アニメーション番号の更新
	/// </summary>
	void Update();

	/// <summary>
	/// イメージレンダラーに画像を設定する
	/// </summary>
	bool ActiveImage();

	/// <summary>
	/// 使用される画像データを設定する
	/// </summary>
	/// <param name="_filePass">ファイルパス</param>
	/// <param name="_xdiv">横方向の分割数</param>
	/// <param name="_ydiv">縦方向の分割数</param>
	/// <param name="_allnum">使用する要素数</param>
	/// <returns>true:成功, false:不正な値</returns>
	bool SetUsedImage(const std::string& _filePass, unsigned int _xdiv, unsigned int _ydiv, unsigned int _allnum = 0U);

	/// <summary>
	/// 再生番号を設定する
	/// </summary>
	/// <param name="_start">開始番号</param>
	/// <param name="_end">終了番号</param>
	/// <returns></returns>
	bool SetPlayNum(unsigned int _start, unsigned int _end);

	/// <summary>
	/// 再生速度を設定する(0.0f以上)
	/// </summary>
	/// <param name="_speed">1秒あたりの再生速度</param>
	/// <returns>true:成功, false:不正な値</returns>
	bool SetPlaySpeed(float _speed);

	/// <summary>
	/// 現在の要素番号を設定
	/// </summary>
	/// <param name="_num">設定したい要素番号</param>
	/// <returns>true:成功, false:startからendの範囲外のためエラー</returns>
	bool SetCurrentNum(unsigned int _num);

	/// <summary>
	/// 逆再生する
	/// </summary>
	void Reverse();

	/// <summary>
	/// 最後のアニメーションかどうか
	/// </summary>
	/// <returns>最後のアニメーション番号ならtrue</returns>
	bool IsEndAnim() const;

	bool loopFlag;

private:
	/// <summary>
	/// 逆再生しているかどうか
	/// </summary>
	/// <returns>true:している, false:していない</returns>
	bool IsPlayBack() const;

private:
	ImageRenderer* renderer;
	std::string filePass;
	unsigned int xdiv, ydiv, allnum;
	int start, end;
	int currentNum;
	float speed;
	float time;
};